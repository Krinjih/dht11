/***********************************************************
FILE:       dht11.cpp
VERSION:    0.0.1
PURPOSE:    Temperature & Humidity Sensor for Arduino

DATASHEET: http://www.micro4you.com/files/sensor/DHT11.pdf


***********************************************************/

#include "dht11.h"

data data::getData(int pin)
{
    data dummy;                                     // Dummyclass for return
    uint8_t dataSet[5] = {0, 0, 0, 0, 0};           // dht11 sends out 5 bytes.
    uint8_t counter = 7;
    uint8_t byteIndex = 0;

    unsigned int timeOut = 100000;                  // time to check if a response is happening

    // only one response per second
    delay(1000);

    // request for data
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // response from dht11
    while (digitalRead(pin) == LOW)
    {
        if (timeOut-- == 0)
        {
            dummy.humidity = -1;
            dummy.temperature = -1;
            dummy.status = 1;
            return dummy;
        }
    }

    timeOut = 100000;
    while (digitalRead(pin) == HIGH)
    {
        if (timeOut-- == 0)
        {
            dummy.humidity = -1;
            dummy.temperature = -1;
            dummy.status = 2;
            return dummy;
        }
    }


    // start of data interchange
    for (int i = 0; i < 40; i++)
    {
        timeOut = 100000;
        while (digitalRead(pin) == LOW)
        {
            if (timeOut-- == 0)
            {
                dummy.humidity = -1;
                dummy.temperature = -1;
                dummy.status = 3;
                return dummy;
            }
        }

        timeOut = 100000;
        long int t = micros();

        // start sending a bit
        while (digitalRead(pin) == HIGH)
        {
            if (timeOut-- == 0)
            {
                dummy.humidity = -1;
                dummy.temperature = -1;
                dummy.status = 4;
                return dummy;
            }
        }

        // 1 and 0 depend on sentTime
        if ((micros()-t) > 40)
        {
            dataSet[byteIndex] |= (1 << counter);

        // if byte is done, go to the next one
        if (counter == 0)
        {
            counter = 7;
            byteIndex++;
        }
        else
        {
            counter--;
        }
    }

    // set 1 and 3 are empty
    dummy.temperature = dataSet[2];
    dummy.humidity = dataSet[0];

    // check if data was sent correct
    if (dataSet[4] == dataSet[0]+dataSet[2])
    {
        dummy.status = 0;
        return dummy;
    }
    else
    {
        dummy.status = 5;
        dummy.humidity = -1;
        dummy.temperature = -1;
        return dummy;
    }

}
