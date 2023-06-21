//
// Created by Justus Krenkel on 18.06.23.
//

#ifndef TUERSTEUERUNG_HARDWARE_H
#define TUERSTEUERUNG_HARDWARE_H

#include <iostream>

class Hardware {
private:

protected:
    unsigned int port;
    unsigned int pin;
    bool status;
    std::string name;

public:
    Hardware(unsigned int port, unsigned int pin, std::string name, bool status);  //Constructor
    ~Hardware();    //Destructor
    std::string getName();

    virtual bool getStatus(); //virtual da in der abgeleiteten Klasse überschrieben
};


#endif //TUERSTEUERUNG_HARDWARE_H
