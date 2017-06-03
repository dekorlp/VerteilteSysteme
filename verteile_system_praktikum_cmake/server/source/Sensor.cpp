/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sensor.cpp
 * Author: michael
 * 
 * Created on 26. April 2017, 21:59
 */

#include "Sensor.h"
#include <string>
#include <iostream>
#include <sstream>

// HALLO TEST

Sensor::Sensor(std::string sensorNr, std::string sensorValue) {
    this->sensorNr = sensorNr;
    this->sensorValue = sensorValue;
}

Sensor::Sensor(const Sensor& orig) {
}

Sensor::~Sensor() {
}

std::string Sensor::GetSensorValue() const {
    return sensorValue;
}

std::string Sensor::GetSensorNr() const {
    return sensorNr;
}

void Sensor::objectOutput() {
    std::cout << "Sensor Nr. [" << this->sensorNr << "]" << "\t Sensor Value= " << this->sensorValue << std::endl;
}

void Sensor::SetSensorValue(std::string sensorValue) {
    this->sensorValue = sensorValue;
}

void Sensor::SetSensorNr(std::string sensorNr) {
    this->sensorNr = sensorNr;
}

std::string Sensor::toString() {
    std::stringstream ss;
    ss << "Sensor Nr. [" << this->sensorNr << "]" << "\t Sensor Value= " << this->sensorValue;
    return ss.str();
}
