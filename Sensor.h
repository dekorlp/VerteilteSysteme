/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Sensor.h
 * Author: michael
 *
 * Created on 26. April 2017, 21:59
 */

#ifndef SENSOR_H
#define SENSOR_H
#include <string>


class Sensor {
public:
    Sensor(std::string sensorNr, std::string sensorValue);
    Sensor(const Sensor& orig);
    virtual ~Sensor();
    
    std::string GetSensorValue() const;
    std::string GetSensorNr() const;
    
    void SetSensorValue(std::string sensorValue);
    void SetSensorNr(std::string sensorNr);
    
    
    std::string toString();
    
    void objectOutput();
    
private:
    std::string sensorNr;
    std::string sensorValue;
};

#endif /* SENSOR_H */

