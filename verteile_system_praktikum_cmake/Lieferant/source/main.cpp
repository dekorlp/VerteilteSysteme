/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mqtt.h"
#include "MqttHandler.h"
#include "Angebot.h"
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <mutex>
#include <string.h>
#include <unistd.h>
#include <ios>
#include <thread>

extern bool isConnected;
extern bool isDisconnected;

std::string ipAdresse = "";
std::string id = "";
int priceMilch = 14;
int priceKaese = 20;
int priceCola = 30;
int priceFleisch = 40;

std::vector<Angebot> angebote;
std::mutex angeboteMutex;
std::mutex memoryAccessMutex;
Mqtt *mqtt;

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{  
    
    memoryAccessMutex.lock();
    char* cMessage;
    cMessage = (char*)calloc( message->payloadlen+1, sizeof(char));
    strcpy( cMessage, (char*)message->payload);
    cMessage[message->payloadlen] = '\0';
    
    std::string sMessage = std::string(cMessage);
    free(cMessage);
    
    
    if(topicName == std::string("Nachfrage/Produzent/Milch"))
    {
        std::cout << "Nachfrage/Produzent/Milch" << sMessage << std::endl;
        // preis#Topic
        mqtt->publish(std::string(std::to_string(priceMilch) +";Bestellung/Produzent/"+id+ "/Milch").c_str(), sMessage.c_str(), 1, onPublishSucceded);
        
    }
    else if(topicName == std::string("Nachfrage/Produzent/Käse"))
    {
        std::cout << "Nachfrage/Produzent/Käse" << std::endl;
        mqtt->publish(std::string(std::to_string(priceKaese) +";Bestellung/Produzent/"+id+ "/Käse").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Nachfrage/Produzent/Cola"))
    {
        std::cout << "Nachfrage/Produzent/Cola" << std::endl;
        mqtt->publish(std::string(std::to_string(priceCola)+";Bestellung/Produzent/"+id+ "/Cola").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Nachfrage/Produzent/Fleisch"))
    {
        std::cout << "Nachfrage/Produzent/Fleisch" << std::endl;
        mqtt->publish(std::string(std::to_string(priceFleisch)+";Bestellung/Produzent/"+id+ "/Fleisch").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Bestellung/Produzent/"+id+ "/Milch"))
    {
        std::cout << "Bestellung/Produzent/"+id+ "/Milch" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(priceMilch)).c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Bestellung/Produzent/"+id+ "/Käse"))
    {
        std::cout << "Bestellung/Produzent/Käse" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(priceKaese)).c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Bestellung/Produzent/"+id+ "/Cola"))
    {
        std::cout << "Bestellung/Produzent/Cola" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(priceCola)).c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Bestellung/Produzent/"+id+ "/Fleisch"))
    {
        std::cout << "Bestellung/Produzent/Fleisch" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(priceFleisch)).c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    
    
    
    // Angebot
    else if(topicName == std::string("Angebot/Produzent/"+id+ "/Milch"))
    {
        
        int price = 0;
        for(Angebot angebot : angebote)
        {
            if(angebot.getProdukt() == "Milch")
            {
                price = angebot.getPrice();
                break;
            }
        }
        
        std::cout << "Angebot/Produzent/Milch" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Angebot/Produzent/"+id+ "/Käse"))
    {
        int price = 0;
        for(Angebot angebot : angebote)
        {
            if(angebot.getProdukt() == "Käse")
            {
                price = angebot.getPrice();
                break;
            }
        }
        
        std::cout << "Angebot/Produzent/Käse" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Angebot/Produzent/"+id+ "/Cola"))
    {
        int price = 0;
        for(Angebot angebot : angebote)
        {
            if(angebot.getProdukt() == "Cola")
            {
                price = angebot.getPrice();
                break;
            }
        }
        
        std::cout << "Angebot/Produzent/Cola" << std::endl;
       mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Angebot/Produzent/"+id+ "/Fleisch"))
    {
        int price = 0;
        for(Angebot angebot : angebote)
        {
            if(angebot.getProdukt() == "Fleisch")
            {
                price = angebot.getPrice();
                break;
            }
        }
        
        std::cout << "Angebot/Produzent/Fleisch" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    memoryAccessMutex.unlock();
    return 1;
}


void checkAngebotGueltigkeit()
{
    while(true)
    {
        std::vector<int> deletableItems;

        for(int i = 0; i < angebote.size(); i++)
        {
            if(angebote.at(i).getGueltigkeit() == 0)
            {
                deletableItems.push_back(i);
            }
            else
            {
                angebote.at(i).setGueltigkeit(angebote.at(i).getGueltigkeit()  -1);
            }
        }

        for(int i = 0; i < deletableItems.size(); i++)
        {
            angeboteMutex.lock();
            angebote.erase(angebote.begin() + deletableItems.at(i));
            angeboteMutex.unlock();
        }

        sleep(2);
    }
}

void subscribeThread()
{
    mqtt = new Mqtt(ipAdresse.c_str(), id.c_str(), connlost, msgarrvd, onConnect, onConnectFailure);    
    while(!isConnected); // warte bis Verbindung aufgebaut ist
    
    mqtt->subscribe("Nachfrage/Produzent/Milch", 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe("Nachfrage/Produzent/Käse", 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe("Nachfrage/Produzent/Cola", 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe("Nachfrage/Produzent/Fleisch", 1, onSubscribeFailure, onSubscribe);
    std::cout << "Besellung/Produzent/"+id+ "/Milch" << std::endl;
    mqtt->subscribe(std::string("Bestellung/Produzent/"+id+ "/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Produzent/"+id+ "/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Produzent/"+id+ "/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Bestellung/Produzent/"+id+ "/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    mqtt->subscribe(std::string("Angebot/Produzent/"+id+ "/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Produzent/"+id+ "/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Produzent/"+id+ "/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Produzent/"+id+ "/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    
    char ch;
    do 
    {
        std::cout << "Angebot erstellen: a" << std::endl;
        std::cout << "Eingabe: " << std::endl;
        if(ch == 'a' || ch == 'A')
        {
            char publishInput;
            do
            {
                std::cout << "Angebot: Milch: m"<<std::endl;
                std::cout << "Angebot: Käse: k"<<std::endl;
                std::cout << "Angebot: Cola: c"<<std::endl;
                std::cout << "Angebot: Fleisch: f"<<std::endl;
                std::cout << "Zurueck: b"<<std::endl;
                std::cout << "Eingabe: ";
                
                if(publishInput == 'm' || publishInput == 'M')
                {
                    int gueltigkeit = 0;
                    int preis = 0;
                    
                    std::cout << "Preis: ";
                    std::cin >> preis;
                    std::cout << std::endl;
                    std::cout << "Gültigkeit: ";
                    std::cin >> gueltigkeit;
                    std::cout << std::endl;
                    
                    Angebot angebot;
                    angebot.setProdukt("Milch");
                    angebot.setPrice(preis);
                    angebot.setGueltigkeit(gueltigkeit);
                    angeboteMutex.lock();
                    angebote.push_back(angebot);
                    angeboteMutex.unlock();
                    mqtt->publish(std::string(std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Produzent/"+id+ "/Milch").c_str(), "Angebot/Shop/Milch", 1, onPublishSucceded);
                    
                }
                else if(publishInput == 'k' || publishInput == 'K')
                {
                    int gueltigkeit = 0;
                    int preis = 0;
                    
                    std::cout << "Preis: ";
                    std::cin >> preis;
                    std::cout << std::endl;
                    std::cout << "Gültigkeit: ";
                    std::cin >> gueltigkeit;
                    std::cout << std::endl;
                    
                    Angebot angebot;
                    angebot.setProdukt("Käse");
                    angebot.setPrice(preis);
                    angebot.setGueltigkeit(gueltigkeit);
                    angeboteMutex.lock();
                    angebote.push_back(angebot);
                    angeboteMutex.unlock();
                    mqtt->publish(std::string(std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Produzent/"+id+ "/Käse").c_str(), "Angebot/Shop/Käse", 1, onPublishSucceded);
                }
                else if(publishInput == 'c' || publishInput == 'C')
                {
                     int gueltigkeit = 0;
                    int preis = 0;
                    
                    std::cout << "Preis: ";
                    std::cin >> preis;
                    std::cout << std::endl;
                    std::cout << "Gültigkeit: ";
                    std::cin >> gueltigkeit;
                    std::cout << std::endl;
                    
                    Angebot angebot;
                    angebot.setProdukt("Cola");
                    angebot.setPrice(preis);
                    angebot.setGueltigkeit(gueltigkeit);
                    angeboteMutex.lock();
                    angebote.push_back(angebot);
                    angeboteMutex.unlock();
                    mqtt->publish(std::string(std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Produzent/"+id+ "/Cola").c_str(), "Angebot/Shop/Cola", 1, onPublishSucceded);
                }
                else if(publishInput == 'f' || publishInput == 'F')
                {
                    int gueltigkeit = 0;
                    int preis = 0;
                    
                    std::cout << "Preis: ";
                    std::cin >> preis;
                    std::cout << std::endl;
                    std::cout << "Gültigkeit: ";
                    std::cin >> gueltigkeit;
                    std::cout << std::endl;
                    
                    Angebot angebot;
                    angebot.setProdukt("Fleisch");
                    angebot.setPrice(preis);
                    angebot.setGueltigkeit(gueltigkeit);
                    angeboteMutex.lock();
                    angebote.push_back(angebot);
                    angeboteMutex.unlock();
                    mqtt->publish(std::string( std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Produzent/"+id+ "/Fleisch").c_str(), "Angebot/Shop/Fleisch", 1, onPublishSucceded);
                }
                std::cin >> publishInput;
                //publishInput = getchar();
                //publishInput = getchar(); // zurzeit nur ein Workaround weil der sonst das Menü zweimal ausgibt!
                std::cout << std::endl;
                std::cout << std::endl;
            }while(publishInput !='B' && publishInput != 'b');
        }
        
        ///ch = getchar();
        std::cin >> ch;
    } while (ch!='Q' && ch != 'q');
    
    mqtt->disconnect(onDisconnect);
    
    while(!isDisconnected); // // warte bis Verbindung abgebaut wurde    
}

int main (int argc, char* argv[])
{
    try {
        if (argc != 7) {
            std::cerr << "Usage: blocking_udp_echo_client <broker> <id> <Preis Milch> <Preis Käse> <Preis Cola> <Preis Fleisch>\n";
            return 1;
        }
    
        ipAdresse = std::string("tcp://"+ std::string(argv[1]) + ":1883");
        id = argv[2];
        priceMilch = std::stoi(argv[3]);
        priceKaese = std::stoi(argv[4]);
        priceCola = std::stoi(argv[5]);
        priceFleisch = std::stoi(argv[6]);
        
        std::thread t1;
        std::thread t2;

        t1 = std::thread(checkAngebotGueltigkeit);
        t2 = std::thread(subscribeThread);
        t1.join();
        t2.join();        
    
    }catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

