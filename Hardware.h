//
// Created by Justus Krenkel on 18.06.23.
//

#ifndef TUERSTEUERUNG_HARDWARE_H
#define TUERSTEUERUNG_HARDWARE_H

#include <iostream>

class Hardware {
private:

public:
    Hardware(unsigned int port, unsigned int pin, std::string name, bool status);  //Constructor
    ~Hardware();    //Destructor
    std::string getName();
    bool getStatus();

protected:
    unsigned int port;
    unsigned int pin;
    bool status;
    std::string name;

};


#endif //TUERSTEUERUNG_HARDWARE_H
