//
// Created by Justus Krenkel on 18.06.23.
//

#ifndef TUERSTEUERUNG_SENSOR_H
#define TUERSTEUERUNG_SENSOR_H

#include <iostream>
#include "Hardware.h"

class Sensor : public Hardware {
private:
    bool activationMode;
protected:

public:
    Sensor(int port, unsigned int pin, std::string name, bool status, bool activationMode); //Constructor
    ~Sensor();
    bool getStatus();
};


#endif //TUERSTEUERUNG_SENSOR_H
