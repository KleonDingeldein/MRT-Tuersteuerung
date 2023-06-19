//
// Created by Justus Krenkel on 18.06.23.
//

#include "Hardware.h"


Hardware::Hardware(unsigned int port, unsigned int pin, std::string name, bool status) :
    port(port),
    pin(pin),
    name(name),
    status(status)
{

}

Hardware::~Hardware() {

}

std::string Hardware::getName() {
    return name;
}

bool Hardware::getStatus() {
    return (status);
}

void Hardware::setStatus(bool newStatus) {
    status = newStatus;
}