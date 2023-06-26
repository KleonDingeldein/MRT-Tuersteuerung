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
#include "DoorInterface.h"
#include "Config.h"
#include "Betriebsmode.h"
#include <chrono>
#include <ctime>
#include <iostream>


class DoorControl {

private:
	DoorInterface door_if;

    Config confReader;
    Betriebsmode *betrieb;



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



    void readHardware();
    void writeHardware();
    int buildcondition();
    int buildentrance();

};


#endif // DOORCONTROL_HH
