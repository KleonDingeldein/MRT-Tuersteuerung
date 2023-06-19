//
// Created by Justus Krenkel on 18.06.23.
//

#include "Sensor.h"


Sensor::Sensor(int port, unsigned int pin, std::string name, bool status, bool activationMode) :
    Hardware(port, pin, name, status),
    activationMode(activationMode)
{

}

Sensor::~Sensor() {}

bool Sensor::getStatus() {

    if(activationMode == status) {
        return(true);
    }

    else {
        return(false);
    }
}