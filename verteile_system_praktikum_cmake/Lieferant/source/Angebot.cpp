/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Angebot.h"

void Angebot::setProdukt(std::string product)
{
    this->product = product;
}

std::string Angebot::getProdukt()
{
    return this->product;
}

void Angebot::setPrice(int price)
{
    this->price = price;
}

int Angebot::getPrice()
{
    return this->price;
}

void Angebot::setGueltigkeit(int gueltigkeit)
{
    this->gueltigkeit = gueltigkeit;
}

int Angebot::getGueltigkeit()
{
    return this->gueltigkeit;
}