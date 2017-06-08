/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mqtt.h
 * Author: dennis
 *
 * Created on 8. Juni 2017, 06:34
 */

#ifndef MQTT_H
#define MQTT_H

#include "../mqtt/MQTTAsync.h"
#include <iostream>

void onSubscribe(void* context, MQTTAsync_successData* response);
void onSubscribeFailure(void* context, MQTTAsync_failureData* response);

class Mqtt
{
    private:
       MQTTAsync client; 
       volatile MQTTAsync_token deliveredtoken;
       char* id;
    public:
        Mqtt(const char *address, const char * id, void (*onConnectionLostHandler)(void*, char*), int (*onMessageReceivedHandler)(void*, char*, int, MQTTAsync_message*), void (*onConnectHandler)(void*, MQTTAsync_successData*),
        void (*onConnectFailureHandler)(void*, MQTTAsync_failureData*));
        void connect(const char *address, const char * id, void (*onConnectionLostHandler)(void*, char*), int (*onMessageReceivedHandler)(void*, char*, int, MQTTAsync_message*), void (*onConnectHandler)(void*, MQTTAsync_successData*),
        void (*onConnectFailureHandler)(void*, MQTTAsync_failureData*));
        void subscribe(const char* topic, int qos, void (*onSubscribeFailureHandler)(void* context, MQTTAsync_failureData* response), void (*onSubscribeSucceededHandler)(void* context, MQTTAsync_successData* response));
        
};


#endif /* MQTT_H */

