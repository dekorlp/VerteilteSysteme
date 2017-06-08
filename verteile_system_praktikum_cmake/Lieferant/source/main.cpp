/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mqtt.h"
#include <iostream>

bool isConnected = false;
bool isDisconnected = false;

void connlost(void *context, char *cause)
{
        MQTTAsync client = (MQTTAsync)context;
        MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
        int rc;

        std::cout << std::endl << "Connection lost" << std::endl << "   cause: " << cause << std::endl;

        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;
        if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
        {
            std::cout << "Failed to start connect, return code: "<< rc << std::endl;
        }
}


int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
    int i;
    char* payloadptr;

    std::cout << std::endl << std::endl;
    std::cout << "Message arrived" << std::endl << "topic: " << topicName << std::endl;
    std::cout << "message: ";
    std::cout << (char*)message->payload<<std::endl;
    
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
    std::cout << "Connect failed, rc" << (response ? response->code : 0) <<std::endl<<std::endl;
}

void onConnect(void* context, MQTTAsync_successData* response)
{
    std::cout << "Succesfull connection!" <<std::endl;
    isConnected = true;
}

void onDisconnect(void* context, MQTTAsync_successData* response)
{
    std::cout << "Successful disconnection"<<std::endl;
    isDisconnected = true;
}

void onSubscribe(void* context, MQTTAsync_successData* response)
{
    std::cout << "Subscribe succeeded!" <<std::endl<<std::endl;
}

void onUnSubscribe(void* context, MQTTAsync_successData* response)
{
    std::cout << "Unsubscribe succeeded!" <<std::endl<<std::endl;
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
    std::cout << "Subscribe failed, rc: " << (response ? response->code : 0) <<std::endl<<std::endl;
}

void onPublishSucceded(void* context, MQTTAsync_successData* response)
{
        printf("Successful published\n");
}

int main ()
{
    
    Mqtt *mqtt = new Mqtt("tcp://192.168.56.3:1883", "12345567", connlost, msgarrvd, onConnect, onConnectFailure);

    while(!isConnected); // warte bis Verbindung aufgebaut ist
    
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

