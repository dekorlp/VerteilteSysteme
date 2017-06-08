/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "MqttHandler.h"



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
    std::cout << "Subscribe succeeded!"<<std::endl<<std::endl;
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