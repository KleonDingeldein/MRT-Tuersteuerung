#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "DoorInterface.h"
#include "Config.h"
#include "DoorInterface.h"
#include "Hardware.h"
#include "Textausgabe.h"
#include "Sensor.h"

// Public:

Config::Config(std::string filename)
{
	std::ifstream input(filename); // lade Datei

	int z=0; // Index für zeilenweiße Einlesen

	bool zustand, activationmode;

	if(input.is_open()) { // wichtig: config-Datei muss in debug-Ordner liege
		std::string line;
	    std::string delimiter = ",";


	    while(std::getline(input, line)) {
	    	std::stringstream linestream(line);
	    	std::string token;

	    	// Port einlesen:
	    	std::getline(linestream, token, ',');
	    	int port=std::stoi(token); // konvertiere token (string) zu integer

	    	// Pin einlesen:
	    	std::getline(linestream, token, ',');
	    	int pin=std::stoi(token);

	    	// Funktion einlesen:
	    	std::getline(linestream, token, ',');
	    	std::string funktion=token;

	    	// Zustand einlesen und zu bool konvertieren:
	    	std::getline(linestream, token, ',');
	    	if(token=="1") {
	    		zustand=true;
	    	}
	    	else  if(token=="0") {
	    		zustand=false;
	    	}

	    	// Aktivationmoden einlesen und zu bool konvertieren:
	    	std::getline(linestream, token, ',');
	    	if(token=="1") {
	    		activationmode=true;
	    	}
	    	else  if(token=="0") {
	    		activationmode=false;
	    	}

			// Objekt anlegen:
			if(port==0||port==1) {
	            sensoren.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
				}
			else if (port==2) {
				aktoren.emplace_back(Aktor(port, pin, funktion, zustand));
	        }

	    	z++;
	    	}
	    }

	    else {
	    	// door_if.DebugString("Konfigurationsdatei konnte nicht eingelesen werden.");
	    	// warum gehts nicht?
	    }
}

Config::~Config()
{

}

bool Config::manuelles_oeffnen() {
	return(ein_Objekt_gesetzt("NTA"));
}

bool Config::manuelles_schliessen() {
	return(ein_Objekt_gesetzt("NTZ"));
}

bool Config::person_vor_tuer() {
	return(ein_Objekt_gesetzt("NVT"));
}

bool Config::person_in_tuer() {
	return(ein_Objekt_gesetzt("NIT"));
}

bool Config::endlage_offen() {
	return(ein_Objekt_gesetzt("ELO"));
}

bool Config::endlage_geschlossen() {
	return(ein_Objekt_gesetzt("ELG"));
}

bool Config::mehrere_sensoren_aktiv() {
	//true sobald 2 sensoren in der liste mit status==1
	// std::vector<Sensor> ELO, ELG, NTA, NTZ, NIT, NVT,
	int z=0; // Anzahl der aktiven Sensoren

	for(int i=0; i<sensoren.size();i++)
	{
		if(sensoren[i].getName()=="NTA"||
		   sensoren[i].getName()=="NTZ"||
		   sensoren[i].getName()=="NIT"||
		   sensoren[i].getName()=="NVT"||
		   sensoren[i].getName()=="ELO"||
		   sensoren[i].getName()=="ELG")
		{
		    if(sensoren[i].getStatus()==true)
		    {
			  z++;
			}
		}

	if(z>1) return(true);
	else return(false);
	}
}

int Config::betriebswahl() {
	// Automatikbetrieb:
	if(ein_Objekt_gesetzt("BW1")&&ein_Objekt_gesetzt("BW2")) return(0);

	// Handbetrieb:
	if(ein_Objekt_gesetzt("BW1")&&!ein_Objekt_gesetzt("BW2")) return(1);

	// Reparaturbetrieb:
	if(!ein_Objekt_gesetzt("BW1")&&ein_Objekt_gesetzt("BW2")) return(2);

	// Aus:
	if(!ein_Objekt_gesetzt("BW1")&&!ein_Objekt_gesetzt("BW2")) return(3);
}

bool Config::oeffnet() {
	// true wenn ein oder mehrere motoren in der liste die tuer oeffnen
	return(ein_Objekt_gesetzt("MO"));
}

bool Config::schliesst() {
	// true wenn ein oder mehrere motoren in der liste die tuer schliessen
	return(ein_Objekt_gesetzt("MC"));
}

bool Config::lampe_leuchtet() {
	return(ein_Objekt_gesetzt("L"));
}

void Config::schliessen() {
	alle_setzen("MC");
}

void Config::oeffnen() {
	alle_setzen("MO");
}

void Config::lampe_an() {
	alle_setzen("L");
}

void Config::lampe_aus() {
	alle_nullen("L");
}

void Config::motoren_stopp() {
	alle_nullen("MC");
	alle_nullen("MO");
}

// Private:

bool Config::ein_Objekt_gesetzt(std::string funktion) {
	// Abfrage für Sensoren:
	if(funktion=="NTA"||
	   funktion=="NTZ"||
	   funktion=="NIT"||
	   funktion=="NVT"||
	   funktion=="ELO"||
	   funktion=="ELG"||
	   funktion=="BW1"||
	   funktion=="BW2")
	{
		for(int i=0; i<sensoren.size();i++)
		{
			if(sensoren[i].getName()==funktion) {
				if(sensoren[i].getStatus()==true) {
					return(true);
				}
			}
		}
		return(false);
	}

	// Abfrage für Aktoren:
	else if(funktion=="MO"||
	        funktion=="MC"||
	        funktion=="L")
	{
		for(int i=0; i<aktoren.size();i++)
		{
			if(aktoren[i].getName()==funktion) {
				if(aktoren[i].getStatus()==true) {
					return(true);
				}
			}
		}
		return(false);
	}



}

void Config::alle_setzen(std::string funktion) {

	for(int i=0; i<aktoren.size();i++) {
		if(aktoren[i].getName()==funktion) {
			aktoren[i].setStatus(1);
		}
	}
}


void Config::alle_nullen(std::string funktion) {
	for(int i=0; i<aktoren.size();i++) {
		if(aktoren[i].getName()==funktion) {
			aktoren[i].setStatus(0);
		}
	}
}

