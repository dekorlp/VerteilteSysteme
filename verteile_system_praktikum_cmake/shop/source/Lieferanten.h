/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lieferanten.h
 * Author: dennis
 *
 * Created on 9. Juni 2017, 10:32
 */

#ifndef LIEFERANTEN_H
#define LIEFERANTEN_H

#include <string>

class Lieferant{
    private:
        std::string lieferantTopic;
        int price;
        bool isSonderangebot;
        int gueltigkeit;
    public:
        void setLieferantTopic(std::string topic);
        std::string getLieferantTopic();
        void setLieferantPrice(int price);
        int getLieferantPrice();
        void setLieferantIsSonderangebot(bool isSonderangebot);
        bool getLieferantIsSonderangebot();
        void setLieferantgueltigkeit(int gueltigkeit);
        int getLieferantgueltigkeit();
        
};

#endif /* LIEFERANTEN_H */

