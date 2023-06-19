//
// Created by Justus Krenkel on 18.06.23.
//

#include "Aktor.h"

Aktor::Aktor(unsigned int port, unsigned int pin, std::string name, bool status) :
    Hardware(port, pin, name, status)

{

}

Aktor::~Aktor() {

}