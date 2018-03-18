/***********************************************************
FILE:       dht11.h
VERSION:    0.0.1
PURPOSE:    Temperature & Humidity Sensor for Arduino

DATASHEET: http://www.micro4you.com/files/sensor/DHT11.pdf


***********************************************************/


#ifndef dht11_h
#define dht11_h

#include "arduino.h"

class data
{
public:
    data getData(int pin);
    int temperature;
    int humidity;
    int status;
};

#endif // dht11_h
