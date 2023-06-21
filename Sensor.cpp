//
// Created by Justus Krenkel on 18.06.23.
//

#include "Sensor.h"

// Constructor
Sensor::Sensor(unsigned int port, unsigned int pin, std::string name, bool status, bool activationMode) :
    Hardware(port, pin, std::move(name), status),
    activationMode(activationMode)
{

}

// Destructor
Sensor::~Sensor() = default;

// Auslesen des Sendorstatus
// 1/true für aktiv oder 0/false für inaktiv
bool Sensor::getStatus()
{

    if(activationMode == status)
    {
        return(true);
    }

    else
    {
        return(false);
    }
}