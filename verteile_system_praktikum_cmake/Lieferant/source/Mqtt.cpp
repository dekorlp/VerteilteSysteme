/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Mqtt.h"

Mqtt::Mqtt(const char *address, const char * id, void (*onConnectionLostHandler)(void*, char*), int (*onMessageReceivedHandler)(void*, char*, int, MQTTAsync_message*), void (*onConnectHandler)(void*, MQTTAsync_successData*),
        void (*onConnectFailureHandler)(void*, MQTTAsync_failureData*))
{
    this->connect(address, id, onConnectionLostHandler, onMessageReceivedHandler, onConnectHandler, onConnectFailureHandler);
}

void Mqtt::connect(const char *address, const char * id, void (*onConnectionLostHandler)(void*, char*), int (*onMessageReceivedHandler)(void*, char*, int, MQTTAsync_message*), void (*onConnectHandler)(void*, MQTTAsync_successData*),
        void (*onConnectFailureHandler)(void*, MQTTAsync_failureData*))
{
    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
    MQTTAsync_token token;
    this->id = (char*)id;
    int rc;
    int ch;

    MQTTAsync_create(&client, address, id, MQTTCLIENT_PERSISTENCE_NONE, NULL);

    MQTTAsync_setCallbacks(client, NULL, onConnectionLostHandler, onMessageReceivedHandler, NULL);

    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnectHandler;
    conn_opts.onFailure = onConnectFailureHandler;
    conn_opts.context = client;
    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
    {
            std::cout << "Failed to start connect, return code" << rc << std::endl;
            exit(-1);       
    }

}

void Mqtt::subscribe(const char* topic, int qos, void (*onSubscribeFailureHandler)(void* context, MQTTAsync_failureData* response), void (*onSubscribeSucceededHandler)(void* context, MQTTAsync_successData* response))
{
    int rc;
    //MQTTAsync client = (MQTTAsync)context;
        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        //MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
    
    
     //printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
     //      "Press Q<Enter> to quit\n\n", topic, id, qos);
    opts.onSuccess = onSubscribeSucceededHandler;
    opts.onFailure = onSubscribeFailureHandler;
    opts.context = client;

    deliveredtoken = 0;
    
    if ((rc = MQTTAsync_subscribe(client, topic, qos, &opts)) != MQTTASYNC_SUCCESS)
    {
        std::cout << "Failed to start subscribe, return code" << std::endl;
        //printf("Failed to start subscribe, return code %d\n", rc);
        exit(-1);       
    }
}