//
// async_udp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// UPLOADED
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iterator>
#include <vector>
#include "Sensor.h"
#include <thread>
#include <sstream>
#include <chrono>
#include <fstream>
#include <map>
#include "MultiCastSender.h"


#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <boost/array.hpp>

#include "gen-cpp/ShopRequest.h"
#include "ShopConnection.h"

using boost::asio::ip::udp;
using boost::asio::ip::tcp;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace std;

int bufferLenghtReset = 0;

int countConnections = 0;
int countSocketClose = 0;
// Sensordaten werden hier gehalten. 
vector<Sensor*> sensorDataList;
map<int, Sensor*> sensorActualMapList;
vector<ProductAnswer> OrderList;
vector<ShopConnection> shopConnections;

mutex m;

string getActualTime() {

    time_t rawtime;
    struct tm * timeinfo;
    char buffer [80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 80, "%a, %d %b %G %T GMT", timeinfo);
    string s = buffer;

    return s;
}

/* HTTP Methoden */
string includeActualSensorData(map<int, Sensor* > mapList) {

    string s;
    for (auto it = mapList.begin(); it != mapList.end(); it++) {
        s += "<p>";
        s += it->second->toString();
        s += "</p>\n";
    }

    return s;
}

string includeSensorHistory(vector<Sensor *> vectorList) {

    string s;
    for (Sensor *sensor : vectorList) {
        s += "<p>";
        s += sensor->toString();
        s += "</p>\n";
    }
    return s;
}

string includeShopBills(vector<ProductAnswer> productList) {
    std::stringstream ss;
    for (ProductAnswer product : productList) {
        ss << "<p>";
        ss << "Sensor Nr. [" << product.sensorId << "]" << "\t Menge = " << product.menge << "\t Preis =" << product.preis;
        ss << "<p>\n";
    }
    return ss.str();
}

void requestOrderButton(string site){
       string option = "";
        //option = site.substr(site.find('?', 0), site.find(' ', 0) - site.find('?', 0));
        option = site.substr(site.find('=', 0) + 1, site.find(' ', 0) - site.find('=', 0));
        site.erase(site.find('?', 0), site.find(' ', 0) - site.find('?', 0));
        cout << "? gefunden -> ausgabe " << option << endl;
        int productId = stoi(option) - 1;

        ProductAnswer productAnswer;

        for (int i = 0; i < shopConnections.size(); i++) {
            //int price = shopConnections.at(i).requestProduct(productId, bestellMenge);
            shopConnections.at(i).setPrice(shopConnections.at(i).requestProduct(productId, 100));
        }

        int cheapestShopIndex = 0;
        for (int i = 1; i < shopConnections.size(); i++) {

            if (shopConnections.at(cheapestShopIndex).getPrice() > shopConnections.at(i).getPrice()) {

                cheapestShopIndex = i;
            }
        }
        cout << "günstigster Preis: " << shopConnections.at(cheapestShopIndex).getPrice() << endl;

        cout << "Bestellung geht raus: " << productId << "-" << 100 << endl;
        //transport->open();
        //client.buyProducts(productAnswer, productId, bestellMenge);
        //transport->close();

        productAnswer = shopConnections.at(cheapestShopIndex).buyProduct(productId, 100);

        m.lock();
        OrderList.push_back(productAnswer);
        m.unlock();
}

const char * sendHTTPSite(string site) {

    ///////////////////////////////////////////////////////////
    // HTTP HEADER 
    string httpHeader;
    httpHeader += "HTTP/1.1 200 OK";
    httpHeader += "\nContent-Type: text/html; charset=utf-8";
    httpHeader += "\nContent-Lenght: ";

    
//    cout << "SEITE AUSGABE" << site << endl;
    string path = "www/";
    path += site;
//    cout << "PATH: " << path << endl;
    // HTML Body wird dynamisch gefuellt.
    string htmlBody = "";
    ifstream myfile(path, ifstream::in);

    if (myfile.is_open()) {
        while (myfile.good()) {
            string line;
            getline(myfile, line);

            htmlBody += line;
            htmlBody += "\n";

            // Wenn html Seite geoffnet wird und die Aktuelle Sensor Daten ausgeben soll
            if (line.find("<!--sensor_actual-->", 0) != -1) {
                htmlBody += includeActualSensorData(sensorActualMapList);
            } else if (line.find("<!--sensor_history-->", 0) != -1) {
                htmlBody += includeSensorHistory(sensorDataList);
            } else if (line.find("<!--shop_bestellungen-->") != -1) {
                // alle Läden durchgehen und die Produktbestellungen ausgeben
                
                for (ShopConnection shopCon : shopConnections) {
                    htmlBody = shopCon.getIpAdress() + "\n";
                    cout << shopCon.getIpAdress() << endl;
                    
                    vector<ProductAnswer> products = shopCon.getBill().produkte;
                    htmlBody += includeShopBills(products);
                    htmlBody += "\n\n";
                }
               
            } else{  
                // falls 404 Error ausgegeben werden soll
                httpHeader = "";
                httpHeader += "HTTP/1.1 404 Not Found";
                httpHeader += "\nContent-Type: text/html; charset=utf-8";
                httpHeader += "\nContent-Lenght: ";
            }
        }
        myfile.close();
    } else {
        // show message:
        std::cerr << "Error: HTML file not exist" << endl;
    }

    int contentLenghtString = htmlBody.size() * sizeof (string::value_type);

    httpHeader += std::to_string(contentLenghtString); // Content lenght wird ermittelt
    httpHeader += "\nConnection: close\n\n";
    httpHeader += htmlBody;

    const char * buffer = httpHeader.c_str();
    return buffer;
}

bool checkIfHTMLRequest(char * c) {

    // wenn in erste Zeile "GET / HTTP1.1" ,dann ist das TCP Paket ein GET - Request
    int i1 = string(c).find("GET", 0);
    int i2 = string(c).find("HTTP", 0);

    if (string(c).find("favicon.ico", 0) != -1) {
        return false;
    } else if (i1 >= 0 && i2 >= 0) {

        return true;
    }

    return false;
}

/*
 * @param 
 */
string parseHTMLRequest(char * stream) {

    string s = stream;
    s = s.erase(0, 5); // löscht GET /
    s = s.substr(0, s.find(' ', 0)); // herausfiltern des HTML Seitennamens 

    cout << "PARSE HTML !!!!!!!!!!!!!!!!!!!!\n\n " << stream << endl;
    cout << "\n\nPARSE HTML END!!!!!!!!!!!!!!!!!!!!\n\n "  << endl;
    
    if(s.size() <= 2){
        s = "zentrale_haupt";
    } else if(s.find("sensoren_akt_status", 0) != -1){
        s = "sensoren_akt_status";
    } else if(s.find("sensoren_historie", 0) != -1){
        s = "sensoren_historie";
    } else if(s.find("shop_bestellungen", 0) != -1){
        s = "shop_bestellungen";
    } else if(s.find("shop_nachbestellen", 0) != -1){
        s = "shop_nachbestellen";
    } else if(s.find("zentrale_haupt", 0) != -1 ){
        s = "zentrale_haupt";
    } else if(s.find('?', 0) != -1){
            requestOrderButton(s);
            s = "shop_nachbestellen";
    } else{
        s = "404Error";
    }
    
    return s;
}

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/* Sensor Methoden */

// Wenn  # gefunden wurde in einer Nachricht handelt es sich um Sensor Daten.

void parseSensorData(string s) {
    string sensorNr = s.substr(0, s.find('#', 0));
    string sensorValue = s.substr(s.find('#', 0) + 1, s.length() - 2);

    Sensor *sensor = new Sensor(sensorNr, sensorValue);

    if (sensorDataList.size() == 200) {
        sensorDataList.clear();
    }

    sensorActualMapList.insert(pair<int, Sensor *>(stoi(sensorNr), sensor));
    sensorActualMapList.at(stoi(sensorNr)) = sensor;
    // actualSensorMap.insert(pair<int, Sensor*>(sensor->GetSensorNr(), sensor));

    sensorDataList.push_back(sensor);
}

bool parseIfSensorData(string s) {
    if (s.find('#', 0) != -1) {
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

/*eigentliche Datenuebertragung*/
class session_TCP {
public:

    session_TCP(boost::asio::io_service& io_service)
    : socket_(io_service) {
    }

    tcp::socket& socket() {
        return socket_;
    }

    void start() {
        
        countConnections++;
        cout << "Connctions: " << countConnections << endl;
        
        socket_.async_read_some(boost::asio::buffer(data_, max_length),
                boost::bind(&session_TCP::handle_read, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        
        
        memset(data_,0,sizeof(data_));
        
        
    }

private:

    void handle_read(const boost::system::error_code& error,
            size_t bytes_transferred) {

        if (!error) {

            string site = "";
            
            // Anfrage ist ein HTTP GET
            if (checkIfHTMLRequest(data_)) {
                site = parseHTMLRequest(data_);
                string s = sendHTTPSite(site);
                size_t responseLenght = s.size() * sizeof (string::value_type);

                // Hier wird die Seite verschickt
                boost::asio::async_write(socket_,
                        boost::asio::buffer(sendHTTPSite(site), responseLenght),
                        boost::bind(&session_TCP::handle_write, this,
                        boost::asio::placeholders::error));
            } else {
                handle_write(error);
            }

        } else {
            this->socket_.close();
            delete this;

            memset(data_,0,sizeof(data_));

            if (error != boost::asio::error::operation_aborted) {

                boost::system::error_code ec;
            }
            countSocketClose++;
            cout << "Count Socket Close: " << countSocketClose << endl;
        }
    }

    void handle_write(const boost::system::error_code& error) {

        memset(data_,0,sizeof(data_));
        
        if (!error) {
            cout << "SOCKET CLOSE" << endl;

            boost::system::error_code ec;

            
            socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
            socket_.close();

            countSocketClose++;
            cout << "Count Socket Close: " << countSocketClose << endl;
        } else {
            if (error != boost::asio::error::operation_aborted) {

                delete this;
                countSocketClose++;
                cout << "Count Socket Close: " << countSocketClose << endl;
                socket_.close();

            }

            //socket_.close();
        }
    }

    tcp::socket socket_;

    enum {
        max_length = 1024
    };
    char data_[max_length];
};

class server_TCP {
public:

    // Warten auf Anfrage vom Client ueber TCP Port

    server_TCP(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
    acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
        start_accept();
    }

private:

    // TCP handshake

    void start_accept() {
        session_TCP* new_session = new session_TCP(io_service_);
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&server_TCP::handle_accept, this, new_session,
                boost::asio::placeholders::error));
    }

    // Hier wird die Session gestarten fuer die Daten Uebertragung

    void handle_accept(session_TCP* new_session,
            const boost::system::error_code& error) {
        if (!error) {
            // Session wird gestartet
            new_session->start();

        } else {
            delete new_session;
        }

        start_accept();
    }

    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
};

class server_UDP {
public:

    server_UDP(boost::asio::io_service& io_service, short port)
    : io_service_(io_service),
    socket_(io_service, udp::endpoint(udp::v4(), port)) {
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&server_UDP::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive_from(const boost::system::error_code& error,
            size_t bytes_recvd) {

        if (!error && bytes_recvd > 0) {

            // Wenn Sensor Daten gefunden
            //        if(parseGiveSensorData(data_)){
            // Hier wird das UDP Paket geparsed und in eine Liste eingefügt

            if (parseIfSensorData(data_)) {
                parseSensorData(data_);

                socket_.async_receive_from(
                        boost::asio::buffer(data_, max_length), sender_endpoint_,
                        boost::bind(&server_UDP::handle_receive_from, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));

            } else {

                // Hier sind die Sensordaten auszugeben.

                std::stringstream stringBuilder;

                for (int i = sensorDataList.size() - 10; i < sensorDataList.size(); i++) {

                    // 2#100;3#80
                    stringBuilder << sensorDataList.at(i)->GetSensorNr() << "#" << sensorDataList.at(i)->GetSensorValue() << ";";
                }

                stringBuilder << "\0";

                char cRequest[8192] = "";
                strcat(cRequest, stringBuilder.str().c_str());
                size_t request_length = stringBuilder.str().size();

                socket_.async_send_to(
                        boost::asio::buffer(cRequest, request_length), sender_endpoint_,
                        boost::bind(&server_UDP::handle_send_to, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
            }

        } else {
            socket_.async_receive_from(
                    boost::asio::buffer(data_, max_length), sender_endpoint_,
                    boost::bind(&server_UDP::handle_receive_from, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
        }
    }

    void handle_send_to(const boost::system::error_code& /*error*/,
            size_t /*bytes_sent*/) {

        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length), sender_endpoint_,
                boost::bind(&server_UDP::handle_receive_from, this,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
    }

private:
    boost::asio::io_service& io_service_;
    udp::socket socket_;
    udp::endpoint sender_endpoint_;

    enum {
        max_length = 1024
    };
    char data_[max_length];
};

void tcpWebserverThread(char * argv) {

    boost::asio::io_service io_service;
    server_TCP s(io_service, atoi(argv));
    io_service.run();
}

void udpSensorServerThread(char* argv) {

    std::cout << "\nI'm ready to receive sensor data\n" << std::endl;

    boost::asio::io_service io_service;
    server_UDP s(io_service, atoi(argv));
    io_service.run();
}

void thriftThread(string multiCastAdress) {


    //cout << "THRIFT THREAD FUNCTION" << endl;

    try {


        while (true) {

            //cout<< "SENSORMAPLIST SIZE: " << sensorActualMapList.size() << endl;
            if (sensorActualMapList.size() >= 2) {
                for (auto& s : sensorActualMapList) {

                    //  int bestellMenge = 100 - stoi(s.second->GetSensorValue());
                    //cout << "SENSORVALUES " << s.second->GetSensorValue() << endl;
                    if (stoi(s.second->GetSensorValue()) <= 20) {

                        int bestellMenge = 100 - stoi(s.second->GetSensorValue());




                        cout << "HALLE WELT Thrift" << endl;
                        //cout << "IN THRIFT THREAD IF VALUE <= 20 "<< endl;
                        //bestellMenge =  bestellMenge;
                        ProductAnswer productAnswer;
                        int productId = stoi(s.second->GetSensorNr());

                        cout << shopConnections.size() << " :SIZE SHOP ONNECTIONS" << endl;
                        for (int i = 0; i < shopConnections.size(); i++) {
                            cout << "SET PRICE " << endl;
                            //int price = shopConnections.at(i).requestProduct(productId, bestellMenge);
                            shopConnections.at(i).setPrice(shopConnections.at(i).requestProduct(productId, bestellMenge));
                        }

                       
                        int cheapestShop = 0;    
                        for(int i = 0; i < shopConnections.size(); i++){
                            if(shopConnections.at(cheapestShop).getPrice() >= shopConnections.at(i).getPrice()){
                                cheapestShop = i;
                            }

                        }                        
                       
                        cout << "günstigster Preis: " << shopConnections.at(cheapestShop).getPrice() << endl;
                        cout << "Bestellung geht raus: " <<  s.second->GetSensorNr() << "-" << bestellMenge<<endl;
                        productAnswer = shopConnections.at(cheapestShop).buyProduct(productId, bestellMenge);
                        	
                        	

                        m.lock();
                        //cout << "ORDER LIST SIZE BEFORE PUSH: " << OrderList.size()<< endl;

                        bool sensorIdExistsInOrderList = false;
                        for (ProductAnswer product : OrderList) {
                            if (product.sensorId == productAnswer.sensorId) {

                            }
                        }
                        OrderList.push_back(productAnswer);
                        //cout << "ORDER LIST SIZE AFTER PUSH: " << OrderList.size()<< endl;
                        m.unlock();

                    }
                }
            }
            sleep(6);
        }


    } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
    }
}

void refillSensorThread() {
    boost::asio::io_service io_service;
    MultiCastSender s(io_service, boost::asio::ip::address::from_string("224.0.0.1"), OrderList, m);
    io_service.run();



}

int main(int argc, char* argv[]) {

    cout << "\nZentrale Server\n\n" << endl;
    /// ShopConnection DEBUG LOCALHOST///
    //ShopConnection localhostShop("localhost");
    //shopConnections.push_back(localhostShop);
    //ShopConnection shopCon("localhost");
    //shopConnections.push_back(shopCon);
    /////////////////////


    try {
        if (argc != 4 && argc != 5) {
            std::cerr << "Please type UDP <port> (Sensor Data), TCP <port> (Webserver) and IP <shop1> and/or IP <shop2>  \n";
            return 1;
        }

        if (argc == 4) {
            ShopConnection shopCon(argv[3]);
            shopConnections.push_back(shopCon);
            cout << "arg == 4: " << argv[3] << endl;
        }

        if (argc == 5) {
            ShopConnection shopCon1(argv[3]);
            shopConnections.push_back(shopCon1);
            cout << "arg == 4: " << argv[3] << endl;

            ShopConnection shopCon(argv[4]);
            shopConnections.push_back(shopCon);
            cout << "arg == 5: " << argv[4] << endl;
        }

        thread t1;
        thread t2;
        thread t3;
        thread t4;

        t1 = thread(udpSensorServerThread, argv[1]);
        t2 = thread(tcpWebserverThread, argv[2]);
        t3 = thread(thriftThread, "224.0.0.1");
        t4 = thread(refillSensorThread);


        t1.join();
        t2.join();
        t3.join();
        t4.join();




    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
