/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: michael
 *
 * Created on 25. Mai 2017, 13:58
 */

// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "../gen-cpp/ShopRequest.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "Mqtt.h"
#include "MqttHandler.h"
#include "Lieferanten.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

Mqtt *mqtt;
std::string id = "";
std::string ipAdresse = "";
extern bool isConnected;
extern bool isDisconnected;

int mengeMilch = 100; // Sensor0
int mengeKaese = 100; // Sensor1
int mengeCola = 100; // Sensor2
int mengeFleisch = 100; // Sensor3

int sensorPrice1 = 2;
int sensorPrice2 = 5;
int sensorPrice3 = 3;
int sensorPrice4 = 4;

Bill bill;
std::vector<Lieferant> lieferanten;
std::mutex lieferantenMutex;
std::mutex memoryAccessMutex;

class ShopRequestHandler : virtual public ShopRequestIf {
public:

    ShopRequestHandler() {
        // Your initialization goes here
    }
    
    int32_t requestProduct(const int32_t sendorId, const int32_t bestellMenge) {
        // Your implementation goes here
        int price;
        
        switch (sendorId) {
            case(0):
                        price = sensorPrice1;
                        
                break;
            case(1):
                        price = sensorPrice2;
                        
                break;
            case(2):
                        price = sensorPrice3;
                        
                break;
            case(3):
                        price = sensorPrice4;
                       
        }
        
        printf("requestProduct\n");
        return price;
    }

    void buyProducts(ProductAnswer& _return, const int32_t sendorId, const int32_t bestellMenge) {
        // Your implementation goes here

        ProductAnswer pA;
     

        pA.sensorId = sendorId;
        
        
        //pA.menge = bestellMenge;
        
        switch (sendorId) {
            case(0):
                if(mengeMilch - bestellMenge <= 0) 
                {
                    pA.menge = 0;
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Milch").c_str(),"Nachfrage/Produzent/Milch", 1, onPublishSucceded);
                }
                else
                {
                    pA.menge = bestellMenge;
                    pA.preis = sensorPrice1;
                    mengeMilch = mengeMilch - bestellMenge;
                    if(mengeMilch <= 40) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Milch").c_str(),"Nachfrage/Produzent/Milch", 1, onPublishSucceded);
                }
                
                    
                break;
            case(1):
                if(mengeKaese - bestellMenge <= 0) 
                {
                    pA.menge = 0;
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Käse").c_str(),"Nachfrage/Produzent/Käse", 1, onPublishSucceded);
                }
                else
                {
                    pA.menge = bestellMenge;
                    pA.preis = sensorPrice2;
                    mengeKaese = mengeMilch - bestellMenge;
                    if(mengeKaese <= 40) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Käse").c_str(),"Nachfrage/Produzent/Käse", 1, onPublishSucceded);
                }
                
                
                    //pA.preis = sensorPrice2;
                    //mengeKaese = mengeKaese - bestellMenge;
                    //if(mengeKaese <= 50) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Käse").c_str(),"Nachfrage/Produzent/Käse", 1, onPublishSucceded);
                break;
            case(2):
                if(mengeCola - bestellMenge <= 0) 
                {
                    pA.menge = 0;
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Cola").c_str(),"Nachfrage/Produzent/Cola", 1, onPublishSucceded);
                }
                else
                {
                    pA.menge = bestellMenge;
                    pA.preis = sensorPrice3;
                    mengeCola = mengeCola - bestellMenge;
                    if(mengeCola <= 40) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Cola").c_str(),"Nachfrage/Produzent/Cola", 1, onPublishSucceded);
                }
                
                
                
                    //pA.preis = sensorPrice3;
                    //mengeCola = mengeCola - bestellMenge;
                    //if(mengeCola <= 40) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Cola").c_str(),"Nachfrage/Produzent/Cola", 1, onPublishSucceded);
                break;
            case(3):
                if(mengeFleisch - bestellMenge <= 0) 
                {
                    pA.menge = 0;
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Fleisch").c_str(),"Nachfrage/Produzent/Fleisch", 1, onPublishSucceded);
                }
                else
                {
                    pA.menge = bestellMenge;
                    pA.preis = sensorPrice4;
                    mengeFleisch = mengeFleisch - bestellMenge;
                    if(mengeFleisch <= 40) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Fleisch").c_str(),"Nachfrage/Produzent/Fleisch", 1, onPublishSucceded);
                }
                
                //pA.preis = sensorPrice4;
                    //mengeFleisch = mengeFleisch - bestellMenge;
                    //if(mengeFleisch <= 40) mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Fleisch").c_str(),"Nachfrage/Produzent/Fleisch", 1, onPublishSucceded);
        }

       
        bill.produkte.push_back(pA);
        _return = pA;
        
        printf("buyProducts\n");
    }

    void getBill(Bill& _return) {
        // Your implementation goes here
        _return = bill;
        //printf("getBill\n");
    }

    void ping() {
        // Your implementation goes here
        printf("ping\n");
    }

};

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    memoryAccessMutex.lock();
    char* cMessage;
    cMessage = (char*)calloc(message->payloadlen+1, sizeof(char));
    strcpy( cMessage, (char*)message->payload);
    cMessage[message->payloadlen] = '\0';
    std::string sMessage = std::string(cMessage);
    free(cMessage);
    memoryAccessMutex.unlock();
    
    if(topicName == std::string("Nachfrage/Shop/"+id+ "/Milch"))
    {
        int positionHash = sMessage.find(';');
        std::string preise = sMessage.substr(0, positionHash);
        std::string bestellungTopic = sMessage.substr(positionHash+1, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(bestellungTopic == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(bestellungTopic);
            lieferant.setLieferantPrice(std::stoi(preise));
            lieferant.setLieferantIsSonderangebot(false);
            lieferant.setLieferantgueltigkeit(0);
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
        
        std::cout << "Nachfrage/Produzent/Milch" << std::endl;
        
    }
    else if(topicName == std::string("Nachfrage/Shop/"+id+ "/Käse"))
    {
        int positionHash = sMessage.find(';');
        std::string preise = sMessage.substr(0, positionHash);
        std::string bestellungTopic = sMessage.substr(positionHash+1, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(bestellungTopic == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(bestellungTopic);
            lieferant.setLieferantPrice(std::stoi(preise));
            lieferant.setLieferantIsSonderangebot(false);
            lieferant.setLieferantgueltigkeit(0);
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
        
        std::cout << "Nachfrage/Produzent/Käse" << std::endl;
    }
    else if(topicName == std::string("Nachfrage/Shop/"+id+ "/Cola"))
    {
        int positionHash = sMessage.find(';');
        std::string preise = sMessage.substr(0, positionHash);
        std::string bestellungTopic = sMessage.substr(positionHash+1, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(bestellungTopic == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(bestellungTopic);
            lieferant.setLieferantPrice(std::stoi(preise));
            lieferant.setLieferantIsSonderangebot(false);
            lieferant.setLieferantgueltigkeit(0);
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
        
        std::cout << "Nachfrage/Produzent/Cola" << std::endl;
    }
    else if(topicName == std::string("Nachfrage/Shop/"+id+ "/Fleisch"))
    {
        int positionHash = sMessage.find(';');
        std::string preise = sMessage.substr(0, positionHash);
        std::string bestellungTopic = sMessage.substr(positionHash+1, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(bestellungTopic == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(bestellungTopic);
            lieferant.setLieferantPrice(std::stoi(preise));
            lieferant.setLieferantIsSonderangebot(false);
            lieferant.setLieferantgueltigkeit(0);
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
        
        std::cout << "Nachfrage/Produzent/Fleisch" << std::endl;
    }
    else if(topicName == std::string("Bestellung/Shop/"+id+ "/Milch"))
    {
        int positionHash = sMessage.find(';');
        std::string menge = sMessage.substr(0, positionHash);
        std::string preis = sMessage.substr(positionHash+1, sMessage.length());
        mengeMilch +=   std::stoi (menge);
        
        std::cout << std::endl << "Milch: " << menge << " für "<< preis << std::endl;
        //std::cout << "Bestand - Milch: " << mengeMilch << std::endl << std::endl;
    }
    else if(topicName == std::string("Bestellung/Shop/"+id+ "/Käse"))
    {
        int positionHash = sMessage.find(';');
        std::string menge = sMessage.substr(0, positionHash);
        std::string preis = sMessage.substr(positionHash+1, sMessage.length());
        mengeKaese += std::stoi (menge);
        
        std::cout << std::endl << "Käse: " << menge << " für "<< preis << std::endl;
        //std::cout << "Bestand - Käse: " << mengeKaese << std::endl << std::endl;
    }
    else if(topicName == std::string("Bestellung/Shop/"+id+ "/Cola"))
    {
        int positionHash = sMessage.find(';');
        std::string menge = sMessage.substr(0, positionHash);
        std::string preis = sMessage.substr(positionHash+1, sMessage.length());
        mengeCola += std::stoi (menge);
        
        std::cout << std::endl << "Cola: " << menge << " für "<< preis << std::endl;
        //std::cout << "Bestand - Cola: " << mengeCola << std::endl << std::endl;
    }
    else if(topicName == std::string("Bestellung/Shop/"+id+ "/Fleisch"))
    {
        int positionHash = sMessage.find(';');
        std::string menge = sMessage.substr(0, positionHash);
        std::string preis = sMessage.substr(positionHash+1, sMessage.length());
        mengeFleisch += std::stoi (menge);
        
        std::cout << std::endl << "Fleisch: " << menge << " für "<< preis << std::endl;
        //std::cout << "Bestand - Fleisch: " << mengeFleisch << std::endl << std::endl;
    }
    
    // Angebot
    else if("Angebot/Shop/Milch")
    {
        int positionHash = sMessage.find(';'); // finde erstes ; -> Preis
        std::string preis = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash +1);
        positionHash = sMessage.find(';'); // finde zweites ; -> Menge
        std::string menge = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        positionHash = sMessage.find(';'); // finde drittes ; -> Menge
        std::string gueltigkeit = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        std::string response = sMessage.substr(0, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(response == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(response);
            lieferant.setLieferantPrice(std::stoi(preis));
            lieferant.setLieferantIsSonderangebot(true);
            lieferant.setLieferantgueltigkeit(std::stoi(gueltigkeit));
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
        
    }
    else if("Angebot/Shop/Käse")
    {
        int positionHash = sMessage.find(';'); // finde erstes ; -> Preis
        std::string preis = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash +1);
        positionHash = sMessage.find(';'); // finde zweites ; -> Menge
        std::string menge = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        positionHash = sMessage.find(';'); // finde drittes ; -> Menge
        std::string gueltigkeit = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        std::string response = sMessage.substr(0, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(response == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(response);
            lieferant.setLieferantPrice(std::stoi(preis));
            lieferant.setLieferantIsSonderangebot(true);
            lieferant.setLieferantgueltigkeit(std::stoi(gueltigkeit));
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
    }
    else if("Angebot/Shop/Cola")
    {
        int positionHash = sMessage.find(';'); // finde erstes ; -> Preis
        std::string preis = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash +1);
        positionHash = sMessage.find(';'); // finde zweites ; -> Menge
        std::string menge = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        positionHash = sMessage.find(';'); // finde drittes ; -> Menge
        std::string gueltigkeit = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        std::string response = sMessage.substr(0, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(response == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(response);
            lieferant.setLieferantPrice(std::stoi(preis));
            lieferant.setLieferantIsSonderangebot(true);
            lieferant.setLieferantgueltigkeit(std::stoi(gueltigkeit));
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
    }
    else if("Angebot/Shop/Fleisch")
    {
        int positionHash = sMessage.find(';'); // finde erstes ; -> Preis
        std::string preis = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash +1);
        positionHash = sMessage.find(';'); // finde zweites ; -> Menge
        std::string menge = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        positionHash = sMessage.find(';'); // finde drittes ; -> Menge
        std::string gueltigkeit = sMessage.substr(0, positionHash);
        sMessage.erase(0, positionHash + 1);
        std::string response = sMessage.substr(0, sMessage.length());
        
        bool lieferantIsInList = false;
        for(Lieferant lieferant : lieferanten)
        {
            if(response == lieferant.getLieferantTopic())
            {
                lieferantIsInList = true;
                
                break;
            }
        }
        
        if(lieferantIsInList == false)
        {
            Lieferant lieferant;
            lieferant.setLieferantTopic(response);
            lieferant.setLieferantPrice(std::stoi(preis));
            lieferant.setLieferantIsSonderangebot(true);
            lieferant.setLieferantgueltigkeit(std::stoi(gueltigkeit));
            
            lieferantenMutex.lock();
            lieferanten.push_back(lieferant);
            lieferantenMutex.unlock();
        }
    }
    
    
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void subscribeThread()
{  
    mqtt = new Mqtt(ipAdresse.c_str(), id.c_str(), connlost, msgarrvd, onConnect, onConnectFailure);    
    while(!isConnected); // warte bis Verbindung aufgebaut ist
    
    
    mqtt->subscribe(std::string("Nachfrage/Shop/"+id+ "/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Nachfrage/Shop/"+id+ "/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Nachfrage/Shop/"+id+ "/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Nachfrage/Shop/"+id+ "/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    mqtt->subscribe(std::string("Bestellung/Shop/"+id+ "/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Shop/"+id+ "/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Shop/"+id+ "/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Shop/"+id+ "/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    mqtt->subscribe(std::string("Bestellung/Shop/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Shop/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Shop/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Shop/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    mqtt->subscribe(std::string("Angebot/Shop/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Shop/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Shop/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Shop/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    char ch;
    do 
    {
        if(ch == 'b' || ch == 'B')
        {
            char publishInput;
            do
            {
                
                std::cout << "Bestellen: Milch: m"<<std::endl;
                std::cout << "Bestellen: Käse: k"<<std::endl;
                std::cout << "Bestellen: Cola: c"<<std::endl;
                std::cout << "Bestellen: Fleisch: f"<<std::endl;
                std::cout << "Zurueck: b"<<std::endl;
                std::cout << "Eingabe: ";
                
                
                if(publishInput == 'm' || publishInput == 'M')
                {
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Milch").c_str(),"Nachfrage/Produzent/Milch", 1, onPublishSucceded);
                }
                else if(publishInput == 'k' || publishInput == 'K')
                {
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Käse").c_str(),"Nachfrage/Produzent/Käse", 1, onPublishSucceded);
                }
                else if(publishInput == 'c' || publishInput == 'C')
                {
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Cola").c_str(),"Nachfrage/Produzent/Cola", 1, onPublishSucceded);
                }
                else if(publishInput == 'f' || publishInput == 'F')
                {
                    mqtt->publish(std::string("Nachfrage/Shop/"+id+ "/Fleisch").c_str(),"Nachfrage/Produzent/Fleisch", 1, onPublishSucceded);
                }
                std::cin >> publishInput;
                //publishInput = getchar();
                //publishInput = getchar(); // zurzeit nur ein Workaround weil der sonst das Menü zweimal ausgibt!
                std::cout << std::endl;
                std::cout << std::endl;
            } while(publishInput !='B' && publishInput != 'b');
        }
        else if(ch == 'a' || ch == 'A')
        {
            char publishInput;
            do
            {
                std::cout << "Ausgabe: Milch: m"<<std::endl;
                std::cout << "Ausgabe: Käse: k"<<std::endl;
                std::cout << "Ausgabe: Cola: c"<<std::endl;
                std::cout << "Ausgabe: Fleisch: f"<<std::endl;
                std::cout << "Zurueck: b"<<std::endl;
                std::cout << "Eingabe: ";


                if(publishInput == 'm' || publishInput == 'M')
                {
                    //std::cout << std::endl << "Milch: " << menge << " für "<< preis << std::endl;
                    std::cout << "Bestand - Milch: " << mengeMilch << std::endl << std::endl;
                }
                else if(publishInput == 'k' || publishInput == 'K')
                {
                    std::cout << "Bestand - Käse: " << mengeKaese << std::endl << std::endl;
                }
                else if(publishInput == 'c' || publishInput == 'C')
                {
                   std::cout << "Bestand - Cola: " << mengeCola << std::endl << std::endl;
                }
                else if(publishInput == 'f' || publishInput == 'F')
                {
                    std::cout << "Bestand - Fleisch: " << mengeFleisch << std::endl << std::endl;
                }
                std::cin >> publishInput;
                //publishInput = getchar();
                //publishInput = getchar(); // zurzeit nur ein Workaround weil der sonst das Menü zweimal ausgibt!
                std::cout << std::endl;
                std::cout << std::endl;
            } while(publishInput !='B' && publishInput != 'b');
        }
            
        
        std::cin >> ch;
    } while (ch!='Q' && ch != 'q');
    
    mqtt->disconnect(onDisconnect);
    
    while(!isDisconnected); // // warte bis Verbindung abgebaut wurde
    
}

void checkCheapiestShopAndBuy()
{
    while(true)
    {
        sleep(2);
        
        // prüfe ob bereits Nachfragen bestehen und gruppiere sie nach ihren Produkten
        // Angebote sollen dabei nicht berücksichtigt werden!
        bool hasLieferantenListNachfrageMilch = false;
        bool hasLieferantenListNachfrageKaese = false;
        bool hasLieferantenListNachfrageCola = false;
        bool hasLieferantenListNachfrageFleisch = false;
        int firstIndexMilch = -1;
        int firstIndexKaese = -1;
        int firstIndexCola = -1;
        int firstIndexFleisch = -1;
        
        int lieferantenIndex = 0;
        for(Lieferant lieferant : lieferanten)
        {
            if(lieferant.getLieferantIsSonderangebot() == false)
            {
                int indexOfSlash = lieferant.getLieferantTopic().find_last_of('/', lieferant.getLieferantTopic().length()-1);
                std::string product = lieferant.getLieferantTopic().substr(indexOfSlash+1, lieferant.getLieferantTopic().length()-1);
                if(product == "Milch" && hasLieferantenListNachfrageMilch == false && firstIndexMilch == -1)
                {
                    hasLieferantenListNachfrageMilch = true;
                    firstIndexMilch = lieferantenIndex;
                }
                else if(product == "Käse" && hasLieferantenListNachfrageKaese == false && firstIndexKaese == -1)
                {
                    hasLieferantenListNachfrageKaese = true;
                    firstIndexKaese = lieferantenIndex;
                }
                else if(product == "Cola" && hasLieferantenListNachfrageCola == false && firstIndexCola == -1)
                {
                    hasLieferantenListNachfrageCola = true;
                    firstIndexCola = lieferantenIndex;
                }
                else if(product == "Fleisch" && hasLieferantenListNachfrageFleisch == false && firstIndexFleisch == -1)
                {
                    hasLieferantenListNachfrageFleisch = true;
                    firstIndexFleisch = lieferantenIndex;
                }
            }
            lieferantenIndex++;
        }
        
        // prüfe ob Nachfrage für Milch vorliegt
        if(hasLieferantenListNachfrageMilch == true)
        {
            
            int cheapestShopIndex = firstIndexMilch;
            for (int i = 0; i < lieferanten.size(); i++) {

                int indexOfSlash = lieferanten.at(i).getLieferantTopic().find_last_of('/', (lieferanten.at(i).getLieferantTopic().length()-1));
                std::string product = lieferanten.at(i).getLieferantTopic().substr(indexOfSlash+1, (lieferanten.at(i).getLieferantTopic().length()-1));
           
                
                if (lieferanten.at(cheapestShopIndex).getLieferantPrice() > lieferanten.at(i).getLieferantPrice() 
                        && product == "Milch") {

                    cheapestShopIndex = i;
                }
            }
            
              mqtt->publish(std::string("Bestellung/Shop/"+id+ "/Milch").c_str(), lieferanten[cheapestShopIndex].getLieferantTopic().c_str(), 1, onPublishSucceded);
            
        }
        
        // prüfe ob Nachfrage für Käse vorliegt
        if(hasLieferantenListNachfrageKaese == true)
        {
            int cheapestShopIndex = firstIndexKaese;
            for (int i = 0; i < lieferanten.size(); i++) {

                int indexOfSlash = lieferanten.at(i).getLieferantTopic().find_last_of('/', (lieferanten.at(i).getLieferantTopic().length()-1));
                std::string product = lieferanten.at(i).getLieferantTopic().substr(indexOfSlash+1, (lieferanten.at(i).getLieferantTopic().length()-1));
           
                
                if (lieferanten.at(cheapestShopIndex).getLieferantPrice() > lieferanten.at(i).getLieferantPrice() 
                        && product == "Käse") {

                    cheapestShopIndex = i;
                }
            }
            
              mqtt->publish(std::string("Bestellung/Shop/"+id+ "/Käse").c_str(), lieferanten[cheapestShopIndex].getLieferantTopic().c_str(), 1, onPublishSucceded);
        }
        
        // prüfe ob Nachfrage für Cola vorliegt
        if(hasLieferantenListNachfrageCola == true)
        {
            int cheapestShopIndex = firstIndexCola;
            for (int i = 0; i < lieferanten.size(); i++) {

                int indexOfSlash = lieferanten.at(i).getLieferantTopic().find_last_of('/', (lieferanten.at(i).getLieferantTopic().length()-1));
                std::string product = lieferanten.at(i).getLieferantTopic().substr(indexOfSlash+1, (lieferanten.at(i).getLieferantTopic().length()-1));
           
                
                if (lieferanten.at(cheapestShopIndex).getLieferantPrice() > lieferanten.at(i).getLieferantPrice() 
                        && product == "Cola") {

                    cheapestShopIndex = i;
                }
            }
            
              mqtt->publish(std::string("Bestellung/Shop/"+id+ "/Cola").c_str(), lieferanten[cheapestShopIndex].getLieferantTopic().c_str(), 1, onPublishSucceded);
        }
        
        // prüfe ob Nachfrage für Fleisch vorliegt
        if(hasLieferantenListNachfrageFleisch == true)
        {
            int cheapestShopIndex = firstIndexFleisch;
            for (int i = 0; i < lieferanten.size(); i++) {

                int indexOfSlash = lieferanten.at(i).getLieferantTopic().find_last_of('/', (lieferanten.at(i).getLieferantTopic().length()-1));
                std::string product = lieferanten.at(i).getLieferantTopic().substr(indexOfSlash+1, (lieferanten.at(i).getLieferantTopic().length()-1));
                
                if (lieferanten.at(cheapestShopIndex).getLieferantPrice() > lieferanten.at(i).getLieferantPrice() 
                        && product == "Fleisch") {
                    
                    cheapestShopIndex = i;
                }
            }

            mqtt->publish(std::string("Bestellung/Shop/"+id+ "/Fleisch").c_str(), lieferanten[cheapestShopIndex].getLieferantTopic().c_str(), 1, onPublishSucceded);
        }
        
        
        // alle nachfragen aus der Liste löschen, da alle nun abgearbeitet wurden
        std::vector<int> deletableItems;
    
        for(int i = 0; i < lieferanten.size(); i++)
        {
            if(lieferanten.at(i).getLieferantIsSonderangebot() == false)
            {
                deletableItems.push_back(i);
            }
        }

        for(int i = 0; i < deletableItems.size(); i++)
        {
            lieferantenMutex.lock();
            lieferanten.erase(lieferanten.begin() + deletableItems.at(i));
            lieferantenMutex.unlock();
        }
        
    }
}

void checkAngebotGueltigkeit()
{
    while(true)
    {
        std::vector<int> deletableItems;

        for(int i = 0; i < lieferanten.size(); i++)
        {
            if(lieferanten.at(i).getLieferantIsSonderangebot() == true)
            {
                if(lieferanten.at(i).getLieferantgueltigkeit() == 0)
                {
                    deletableItems.push_back(i);
                }
                else
                {
                    lieferanten.at(i).setLieferantgueltigkeit(lieferanten.at(i).getLieferantgueltigkeit()-1);
                }
            }
        }

        for(int i = 0; i < deletableItems.size(); i++)
        {
            lieferantenMutex.lock();
            lieferanten.erase(lieferanten.begin() + deletableItems.at(i));
            lieferantenMutex.unlock();
        }

        sleep(1);
    }
}

void thriftThread()
{
    int port = 9090;
    shared_ptr<ShopRequestHandler> handler(new ShopRequestHandler());
    shared_ptr<TProcessor> processor(new ShopRequestProcessor(handler));
    shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();
}

int main(int argc, char **argv) {
    
     try {
        if (argc != 3) {
            std::cerr << "Usage: blocking_udp_echo_client <broker> <id>\n";
            return 1;
        }
    
        ipAdresse = std::string("tcp://"+ std::string(argv[1]) + ":1883");
        id = argv[2];
    
    std::cout << "Preis für Sensor 1: ";
    std::cin >> sensorPrice1;
    std::cout << std::endl;
    
    std::cout << "Preis für Sensor 2: ";
    std::cin >> sensorPrice2;
    std::cout << std::endl;
    
    std::cout << "Preis für Sensor 3: ";
    std::cin >> sensorPrice3;
    std::cout << std::endl;
    
    std::cout << "Preis für Sensor 4: ";
    std::cin >> sensorPrice4;
    std::cout << std::endl;
    
    std::thread t1;
    std::thread t2;
    std::thread t3;
    std::thread t4;
    
    t2 = std::thread(thriftThread);
    t1 = std::thread(subscribeThread);
    t3 = std::thread(checkCheapiestShopAndBuy);
    t4 = std::thread(checkAngebotGueltigkeit);
  
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    
     }catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
     
    return 0;
}
