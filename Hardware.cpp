//
// Created by Justus Krenkel on 18.06.23.
//

#include "Hardware.h"

// Constructor
Hardware::Hardware(unsigned int port, unsigned int pin, std::string name, bool status) :
    port(port),
    pin(pin),
    name(std::move(name)),
    status(status)
{

}

// Destructor
Hardware::~Hardware() = default;

// Funktion liefert einen string mit dem Namen der Instanz zurück
std::string Hardware::getName() {
    return name;
}

// Funktion liefert des Status der Instanz zurück
// 1/true für aktiv oder 0/false für inaktiv
bool Hardware::getStatus() {
    return (status);
}
