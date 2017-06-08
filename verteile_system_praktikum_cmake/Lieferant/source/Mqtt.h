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

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../mqtt/MQTTAsync.h"
#include "unistd.h"
#include <thread>

void onConnectFailure(void* context, MQTTAsync_failureData* response);
void onConnect(void* context, MQTTAsync_successData* response);
void connlost(void *context, char *cause);
int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message);


class Mqtt
{
    private:
       MQTTAsync client; 
    public:
        void connect(const char *address, const char * id);
        
};


#endif /* MQTT_H */

