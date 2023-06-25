//
// Created by Justus Krenkel on 18.06.23.
//

#ifndef TUERSTEUERUNG_SENSOR_H
#define TUERSTEUERUNG_SENSOR_H

#include <iostream>
#include "Hardware.h"

//Sensor erbt von Hardware
class Sensor : public Hardware {
private:
    const bool activationMode;    // high-active oder low-active

protected:

public:
    Sensor(int port, int pin, std::string name, bool status, bool activationMode);     //Constructor
    ~Sensor();          //Destructor
    bool getStatus();   // liefert true bzw. 1, wenn der Sensor aktiv ist und false bzw. 0, wenn der Sensor inaktiv ist.

};



#endif /* SENSOR_H_ */
