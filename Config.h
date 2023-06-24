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
	// Einlesen der Config-Datei:
	void read(std::string filename);

	// Auswahl der Betriebsart
	Sensor BW1, BW2;

	// Vekotoren (keine Arrays) weil man angeblich über "name".emplace(Element) dynamische vergrößern kann
	std::vector<Sensor> sensorliste;
	std::vector<Aktor> aktorliste;

protected:


public:
    Config(std::string datei);
    ~Config();

    // Funktionen welche von Betriebsarten benötigtt werden:
    

};


#endif //TUERSTEUERUNG_CONFIG_H
