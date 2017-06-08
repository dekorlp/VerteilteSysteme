/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mqtt.h"
#include "MqttHandler.h"
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <string.h>

extern bool isConnected;
extern bool isDisconnected;

std::string id = "Milchbauer";
std::list<std::string> subscriptedTopicsList;


int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    int length = message->payloadlen;
    std::stringstream bestellungMilchStringBuilder;
    bestellungMilchStringBuilder << "Bestellung/Produzent/" << id << "/Milch";
   
    char* cMessage;
    cMessage = (char*)calloc( length+1, sizeof(char));
    strcpy( cMessage, (char*)message->payload);
    cMessage[length+1] = '\0';
    
    if(topicName == std::string("Nachfrage/Produzent/Milch"))
    {
        std::cout << "Nachfrage/Produzent/Milch" << cMessage << std::endl;
    }
    else if(topicName == std::string("Nachfrage/Produzent/Käse"))
    {
        std::cout << "Nachfrage/Produzent/Käse" << std::endl;
    }
    else if(topicName == std::string("Nachfrage/Produzent/Cola"))
    {
        std::cout << "Nachfrage/Produzent/Cola" << std::endl;
    }
    else if(topicName == std::string("Nachfrage/Produzent/Fleisch"))
    {
        std::cout << "Nachfrage/Produzent/Fleisch" << std::endl;
    }
    
    std::cout << std::endl << std::endl;
    std::cout << "Message arrived" << std::endl << "topic: " << topicName << std::endl;
    std::cout << "message: ";
    std::cout << (char*)message->payload<<std::endl;
    
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}




int main ()
{
    std::string ipAdresse = "tcp://192.168.56.3:1883";
    
    
    Mqtt *mqtt = new Mqtt(ipAdresse.c_str(), id.c_str(), connlost, msgarrvd, onConnect, onConnectFailure);    
    while(!isConnected); // warte bis Verbindung aufgebaut ist
    
    std::stringstream bestellungMilchStringBuilder;
    bestellungMilchStringBuilder << "Bestellung/Produzent/" << id << "/Milch";
    
    mqtt->subscribe("Nachfrage/Produzent/Milch", 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe("Nachfrage/Produzent/Käse", 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe("Nachfrage/Produzent/Cola", 1, onSubscribeFailure, onSubscribe);
    mqtt->subscribe("Nachfrage/Produzent/Fleisch", 1, onSubscribeFailure, onSubscribe);
    
    int ch;
    do 
    {
        if(ch == 's' || ch == 's')
        {
            mqtt->subscribe("hda/test", 1, onSubscribeFailure, onSubscribe);
        }
        
        if(ch == 'p' || ch == 'P')
        {
            mqtt->publish("Meine Nachricht", "hda/test", 1, onPublishSucceded);
        }
        
        if(ch == 'u' || ch == 'U')
        {
            mqtt->unsubscribe("hda/test", onUnSubscribe);
        }
        
        ch = getchar();
    } while (ch!='Q' && ch != 'q');
    
    mqtt->disconnect(onDisconnect);
    
    while(!isDisconnected); // // warte bis Verbindung abgebaut wurde
    
    // Subscribe
    //std::thread t1;
    
    //t1 = std::thread(subscribeThread);
    //t1.join();
    
}

