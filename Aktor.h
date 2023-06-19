//
// Created by Justus Krenkel on 18.06.23.
//

#ifndef TUERSTEUERUNG_AKTOR_H
#define TUERSTEUERUNG_AKTOR_H

#include "Hardware.h"

//Klasse Aktor erbt/abgeleitet von Hardware
class Aktor : public Hardware {
private:

protected:


public:
	Aktor(unsigned int port, unsigned int pin, std::string name, bool status);      //Constructor
    ~Aktor();       //Destructor
    void setStatus(bool newStatus);

};


#endif //TUERSTEUERUNG_AKTOR_H
