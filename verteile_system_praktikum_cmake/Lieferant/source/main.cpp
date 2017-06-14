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
#include <list>
#include <string.h>

extern bool isConnected;
extern bool isDisconnected;

std::string id = "Milchbauer";
int priceMilch = 14;
int priceKaese = 20;
int priceCola = 30;
int priceFleisch = 40;

std::list<std::string> subscriptedTopicsList;
std::list<Angebot> angebote;
Mqtt *mqtt;

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    std::stringstream bestellungMilchStringBuilder;
    bestellungMilchStringBuilder << "Bestellung/Produzent/" << id << "/Milch";
   
    char* cMessage;
    cMessage = (char*)calloc( message->payloadlen+1, sizeof(char));
    strcpy( cMessage, (char*)message->payload);
    cMessage[message->payloadlen] = '\0';
    
    std::string sMessage = std::string(cMessage);
    
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
    else if(topicName == std::string("Angebot/Lieferant/"+id+ "/Milch"))
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
        
        std::cout << "Angebot/Lieferant/Milch" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Angebot/Lieferant/"+id+ "/Käse"))
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
        
        std::cout << "Angebot/Lieferant/Käse" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Angebot/Lieferant/"+id+ "/Cola"))
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
        
        std::cout << "Angebot/Lieferant/Cola" << std::endl;
       mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    else if(topicName == std::string("Angebot/Lieferant/"+id+ "/Fleisch"))
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
        
        std::cout << "Angebot/Lieferant/Fleisch" << std::endl;
        mqtt->publish(std::string("20;"+std::to_string(price)+"").c_str(), sMessage.c_str(), 1, onPublishSucceded);
    }
    
    //std::cout << std::endl << std::endl;
    //std::cout << "Message arrived" << std::endl << "topic: " << topicName << std::endl;
    //std::cout << "message: ";
    //std::cout << (char*)message->payload<<std::endl;
    
    free(cMessage);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}




int main ()
{
    std::string ipAdresse = "tcp://192.168.56.3:1883";
    
    
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
    
    mqtt->subscribe(std::string("Angebot/Lieferant/"+id+ "/Milch").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Lieferant/"+id+ "/Käse").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Lieferant/"+id+ "/Cola").c_str(), 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe(std::string("Angebot/Lieferant/"+id+ "/Fleisch").c_str(), 1, onSubscribeFailure, onSubscribe);
    
    
    int ch;
    do 
    {
        std::cout << "Angebot erstellen: a" << std::endl;
        std::cout << "Eingabe: " << std::endl;
        if(ch == 'a' || ch == 'A')
        {
            int publishInput;
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
                    angebote.push_back(angebot);
                    mqtt->publish(std::string(std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Lieferant/"+id+ "/Milch").c_str(), "Angebot/Shop/Milch", 1, onPublishSucceded);
                    
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
                    angebote.push_back(angebot);
                    mqtt->publish(std::string(std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Lieferant/"+id+ "/Käse").c_str(), "Angebot/Shop/Käse", 1, onPublishSucceded);
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
                    angebote.push_back(angebot);
                    mqtt->publish(std::string(std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Lieferant/"+id+ "/Cola").c_str(), "Angebot/Shop/Cola", 1, onPublishSucceded);
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
                    angebote.push_back(angebot);
                    mqtt->publish(std::string( std::to_string(preis) + ";" + "20;" + std::to_string(gueltigkeit) + ";Angebot/Lieferant/"+id+ "/Fleisch").c_str(), "Angebot/Shop/Fleisch", 1, onPublishSucceded);
                }
                publishInput = getchar();
                publishInput = getchar(); // zurzeit nur ein Workaround weil der sonst das Menü zweimal ausgibt!
                std::cout << std::endl;
                std::cout << std::endl;
            }while(publishInput !='B' && publishInput != 'b');
        }
        
        //if(ch == 's' || ch == 's')
        //{
        //    mqtt->subscribe("hda/test", 1, onSubscribeFailure, onSubscribe);
        //}
        
        //if(ch == 'p' || ch == 'P')
        //{
        //    mqtt->publish("Meine Nachricht", "hda/test", 1, onPublishSucceded);
        //}
        
        //if(ch == 'u' || ch == 'U')
        //{
        //    mqtt->unsubscribe("hda/test", onUnSubscribe);
        //}
        
        ch = getchar();
    } while (ch!='Q' && ch != 'q');
    
    mqtt->disconnect(onDisconnect);
    
    while(!isDisconnected); // // warte bis Verbindung abgebaut wurde
    
    // Subscribe
    //std::thread t1;
    
    //t1 = std::thread(subscribeThread);
    //t1.join();
    
}

