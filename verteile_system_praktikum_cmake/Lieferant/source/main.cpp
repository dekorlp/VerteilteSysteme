/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mqtt.h"
#include <iostream>

bool isConnected = false;

void connlost(void *context, char *cause)
{
        MQTTAsync client = (MQTTAsync)context;
        MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
        int rc;

        std::cout << std::endl << "Connection lost" << std::endl << "   cause: " << cause << std::endl;
        //printf("\nConnection lost\n");
        //printf("     cause: %s\n", cause);

        //printf("Reconnecting\n");
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

    std::cout << "Message arrived" << std::endl << "topic: " << topicName << std::endl;
    std::cout << "message: ";
    payloadptr = (char*) message->payload;
    for(i=0; i<message->payloadlen; i++)
    {
        putchar(*payloadptr++);
    }
    putchar('\n');
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

void onSubscribe(void* context, MQTTAsync_successData* response)
{
    std::cout << "Subscribe succeeded!" <<std::endl<<std::endl;
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response)
{
    std::cout << "Subscribe failed, rc: " << (response ? response->code : 0) <<std::endl<<std::endl;
}

int main ()
{
    
    Mqtt *mqtt = new Mqtt("tcp://192.168.56.3:1883", "12345567", connlost, msgarrvd, onConnect, onConnectFailure);
    //mqtt.connect();
    
    while(!isConnected); // warte bis Verbindung aufgebaut ist
    
    mqtt->subscribe("hda/test", 1, onSubscribeFailure, onSubscribe);
    
    while(true)
    {
        
    }
    
    // Subscribe
    //std::thread t1;
    
    //t1 = std::thread(subscribeThread);
    //t1.join();
    
}

