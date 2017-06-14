/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Angebot.h
 * Author: dennis
 *
 * Created on 9. Juni 2017, 13:35
 */

#ifndef ANGEBOT_H
#define ANGEBOT_H

#include <string>

class Angebot{
    private:
        std::string product;
        int price;
        int gueltigkeit;
    public:
        void setProdukt(std::string product);
        std::string getProdukt();
        void setPrice(int price);
        int getPrice();
        void setGueltigkeit(int gueltigkeit);
        int getGueltigkeit();          
};


#endif /* ANGEBOT_H */

