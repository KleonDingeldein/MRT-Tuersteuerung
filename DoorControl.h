/*  -*- mode: c++; -*-

 * Praktikum MRT2 
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r3
 */

#ifndef DOORCONTROL_HH
#define DOORCONTROL_HH

#include "ncurses.h"
#include "Betriebsmode.h"
#include "DoorInterface.h"
#include "Config.h"

#include <chrono>
#include <ctime>
#include <iostream>

class DoorControl {

private:
	DoorInterface door_if;

    Betriebsmode betrieb;
    //Betriebsmode *betrieb;

    //Sensoren - für Hardware Read
    unsigned char pins_port_0;
    unsigned char pins_port_1;

    //Aktoren - für Hardware Write
    unsigned char pins_port_2 = 0;

protected:

public:
    DoorControl();
    ~DoorControl();



    void run();
    void writeLog(std::string sLog, bool noNewLine = 0);
    void readHardware(Config *conf);
    void writeHardware(Config *conf);

    int buildcondition(Config *configReader);
    int buildentrance(Config *configReader);

};


#endif // DOORCONTROL_HH
