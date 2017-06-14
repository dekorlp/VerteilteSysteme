/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Lieferanten.h"

void Lieferant::setLieferantTopic(std::string topic)
{
    this->lieferantTopic = topic;
}

std::string Lieferant::getLieferantTopic()
{
    return this->lieferantTopic;
}

void Lieferant::setLieferantPrice(int price)
{
    this->price = price;
}

int Lieferant::getLieferantPrice()
{
    return this->price;
}

void Lieferant::setLieferantIsSonderangebot(bool isSonderangebot)
{
    this->isSonderangebot =  isSonderangebot;
}

bool Lieferant::getLieferantIsSonderangebot()
{
    return isSonderangebot;
}
        
void Lieferant::setLieferantgueltigkeit(int gueltigkeit)
{
    this->gueltigkeit = gueltigkeit;
}

int Lieferant::getLieferantgueltigkeit()
{
    return gueltigkeit;
}