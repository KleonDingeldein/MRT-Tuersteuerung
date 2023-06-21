//
// Created by Justus Krenkel on 20.06.23.
//

#ifndef TUERSTEUERUNG_CONFIG_H
#define TUERSTEUERUNG_CONFIG_H

#include <iostream>
#include <vector>
#include "Aktor.h"
#include "Sensor.h"
#include "DoorInterface.h"


class Config {
private:
protected:
public:
    Config();
    ~Config();

    void read(std::string filename);
};


#endif //TUERSTEUERUNG_CONFIG_H
