//
// Created by Justus Krenkel on 18.06.23.
//

#include "Aktor.h"
#include "Hardware.h"

// Constructor
Aktor::Aktor(int port, int pin, std::string name, bool status) :
    Hardware(port, pin, std::move(name), status)

{

}

// Destructor
Aktor::~Aktor() = default;

// Funktion setzt den Status des Aktors
// 1/an oder 0/aus
void Aktor::setStatus(bool newStatus) {
    status = newStatus;
}

