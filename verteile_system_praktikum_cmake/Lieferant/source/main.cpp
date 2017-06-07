
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../mqtt/MQTTAsync.h"
#include "unistd.h"
#include <thread>

volatile MQTTAsync_token deliveredtoken;
int finished = 0;

#define ADDRESS     "tcp://192.168.2.118:1883"
#define CLIENTID    "Publisher"
#define TOPIC       "test/topic"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

    void connlost(void *context, char *cause)
{
        MQTTAsync client = (MQTTAsync)context;
        MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
        int rc;

        printf("\nConnection lost\n");
        printf("     cause: %s\n", cause);

        printf("Reconnecting\n");
        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;
        if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
        {
                printf("Failed to start connect, return code %d\n", rc);
                finished = 1;
        }
}


void onDisconnect(void* context, MQTTAsync_successData* response)
{
        printf("Successful disconnection\n");
        finished = 1;
}


void onSend(void* context, MQTTAsync_successData* response)
{
        MQTTAsync client = (MQTTAsync)context;
        MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
        int rc;

        printf("Message with token value %d delivery confirmed\n", response->token);

        opts.onSuccess = onDisconnect;
        opts.context = client;

        if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
        {
                printf("Failed to start sendMessage, return code %d\n", rc);
                exit(-1);       
        }
}


void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
        printf("Connect failed, rc %d\n", response ? response->code : 0);
        finished = 1;
}


void onConnect(void* context, MQTTAsync_successData* response)
{
        MQTTAsync client = (MQTTAsync)context;
        MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
        MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
        int rc;

        printf("Successful connection\n");
        
        opts.onSuccess = onSend;
        opts.context = client;

        pubmsg.payload = (void *) PAYLOAD;
        pubmsg.payloadlen = strlen(PAYLOAD);
        pubmsg.qos = QOS;
        pubmsg.retained = 0;
        deliveredtoken = 0;

        if ((rc = MQTTAsync_sendMessage(client, TOPIC, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
        {
                printf("Failed to start sendMessage, return code %d\n", rc);
                exit(-1);       
        }
}

void subscribeThread()
{
    
}

int main ()
{
    // Subscribe
    std::thread t1;
    
    t1 = std::thread(subscribeThread);
    t1.join();
    
    
    
}

