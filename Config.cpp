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

	    	objekt_anlegen(port, pin, funktion, zustand, activationmode);

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
	return(ein_Objekt_gesetzt(NTA));
}

bool Config::manuelles_schliessen() {
	return(ein_Objekt_gesetzt(NTZ));
}

bool Config::person_vor_tuer() {
	return(ein_Objekt_gesetzt(NVT));
}

bool Config::person_in_tuer() {
	return(ein_Objekt_gesetzt(NIT));
}

bool Config::endlage_offen() {
	return(ein_Objekt_gesetzt(ELO));
}

bool Config::endlage_geschlossen() {
	return(ein_Objekt_gesetzt(ELG));
}

bool Config::mehrere_sensoren_aktiv() {
	//true sobald 2 sensoren in der liste mit status==1
	// std::vector<Sensor> ELO, ELG, NTA, NTZ, NIT, NVT,
	int z=0; // Anzahl der aktiven Sensoren

	for(int i=0; i<ELO.size();i++){
		if(ELO[i].getStatus()==true) {
			z++;
		}
	}

	if(z>1) return(true);

	for(int i=0; i<ELG.size();i++){
		if(ELG[i].getStatus()==true) {
			z++;
		}
	}

	if(z>1) return(true);

	for(int i=0; i<NTA.size();i++){
		if(NTA[i].getStatus()==true) {
			z++;
		}
	}

	if(z>1) return(true);

	for(int i=0; i<NTZ.size();i++){
		if(NTZ[i].getStatus()==true) {
			z++;
		}
	}

	for(int i=0; i<NIT.size();i++){
		if(NIT[i].getStatus()==true) {
			z++;
		}
	}

	if(z>1) return(true);

	for(int i=0; i<NVT.size();i++){
		if(NVT[i].getStatus()==true) {
			z++;
		}
	}

	if(z>1) return(true);
	else return(false);
}

int Config::betriebswahl() {
	// Automatikbetrieb:
	if(ein_Objekt_gesetzt(BW1)&&ein_Objekt_gesetzt(BW2)) return(0);

	// Handbetrieb:
	if(ein_Objekt_gesetzt(BW1)&&!ein_Objekt_gesetzt(BW2)) return(1);

	// Reparaturbetrieb:
	if(!ein_Objekt_gesetzt(BW1)&&ein_Objekt_gesetzt(BW2)) return(2);

	// Aus:
	if(!ein_Objekt_gesetzt(BW1)&&!ein_Objekt_gesetzt(BW2)) return(3);
}

bool Config::oeffnet() {
	// true wenn ein oder mehrere motoren in der liste die tuer oeffnen
	return(ein_Objekt_gesetzt(OPEN));
}

bool Config::schliesst() {
	// true wenn ein oder mehrere motoren in der liste die tuer schliessen
	return(ein_Objekt_gesetzt(CLOSE));
}

bool Config::lampe_leuchtet() {
	return(ein_Objekt_gesetzt(LIGHT));
}

void Config::schliessen() {
	alle_setzen(CLOSE);
}

void Config::oeffnen() {
	alle_setzen(OPEN);
}

void Config::lampe_an() {
	alle_setzen(LIGHT);
}

void Config::lampe_aus() {
	alle_nullen(LIGHT);
}

void Config::motoren_stopp() {
	alle_nullen(OPEN);
	alle_nullen(CLOSE);
}

// Private:

void Config::objekt_anlegen(int pin, int port, std::string funktion, bool zustand, bool activationmode) {
	// Eingelesenes Objekt in Vektoren schreiben

	if(funktion=="ELO") {
	   ELO.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
    else if (funktion=="ELG") {
	   ELG.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="NTA") {
		NTA.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="NTZ") {
		NTZ.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="NIT") {
		NIT.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="NVT") {
		NVT.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="BW1") {
		BW1.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="BW2") {
		BW2.emplace_back(Sensor(port, pin, funktion, zustand, activationmode));
	}
	else if (funktion=="OPEN") {
		OPEN.emplace_back(Aktor(port, pin, funktion, zustand));
	}
	else if (funktion=="CLOSE") {
		CLOSE.emplace_back(Aktor(port, pin, funktion, zustand));
	}
	else if (funktion=="LIGHT") {
		LIGHT.emplace_back(Aktor(port, pin, funktion, zustand));
	}
}

bool Config::ein_Objekt_gesetzt(std::vector<Sensor> liste) {
	for(int i=0; i<liste.size();i++){
		if(liste[i].getStatus()==true) {
			return(true);
		}
	}
	return(false);
}

bool Config::ein_Objekt_gesetzt(std::vector<Aktor> liste) {
	for(int i=0; i<liste.size();i++){
		if(liste[i].getStatus()==true) {
			return(true);
		}
	}
	return(false);
}

void Config::alle_setzen(std::vector<Aktor> liste) {
	for(int i=0; i<liste.size();i++){
		liste[i].setStatus(1);
	}
}

void Config::alle_nullen(std::vector<Aktor> liste) {
	for(int i=0; i<liste.size();i++){
		liste[i].setStatus(0);
	}
}

