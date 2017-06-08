/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MqttHandler.h
 * Author: dennis
 *
 * Created on 8. Juni 2017, 13:57
 */

#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H
#include "Mqtt.h"
#include <iostream>

//int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message);

void connlost(void *context, char *cause);

void onConnectFailure(void* context, MQTTAsync_failureData* response);

void onConnect(void* context, MQTTAsync_successData* response);

void onDisconnect(void* context, MQTTAsync_successData* response);

void onSubscribe(void* context, MQTTAsync_successData* response);

void onUnSubscribe(void* context, MQTTAsync_successData* response);

void onSubscribeFailure(void* context, MQTTAsync_failureData* response);

void onPublishSucceded(void* context, MQTTAsync_successData* response);

#endif /* MQTTHANDLER_H */

