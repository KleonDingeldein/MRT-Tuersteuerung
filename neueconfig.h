
#ifndef TUERSTEUERUNG_CONFIG_H
#define TUERSTEUERUNG_CONFIG_H

#include <iostream>
#include <vector>
#include "Aktor.h"
#include "Sensor.h"
#include "DoorInterface.h"


class Config {
private:
	// void objekt_anlegen(int pin, int port, std::string funktion, bool zustand, bool activationmode);
	bool ein_Objekt_gesetzt(std::string funktion);
	void alle_setzen(std::string funktion);
	void alle_nullen(std::string funktion);

protected:


public:
    Config(std::string filename);
    ~Config();

    // Vekotoren der Hardware-Kategorien:
    std::vector<Sensor> sensoren;
	std::vector<Aktor> aktoren;

    // Funktionen welche von Betriebsarten benötigt werden:
    // Sensoraktivitaeten:
    bool manuelles_oeffnen();
    bool manuelles_schliessen();
    bool person_vor_tuer();
    bool person_in_tuer();
    bool endlage_offen();
    bool endlage_geschlossen();
    bool mehrere_sensoren_aktiv();   //true sobald 2 sensoren in der liste mit status==1

    // Rückgabe der Betriebswahl:
    int betriebswahl();

    // Aktoraktivitaeten:
    bool oeffnet();          // true wenn ein oder mehrere motoren in der liste die tuer oeffnen
    bool schliesst();        // true wenn ein oder mehrere motoren in der liste die tuer schliessen
    bool lampe_leuchtet();   //nicht zwingend noetig

    // Steuern der Aktoren:
    void schliessen();         // alle oeffnermotoren aktiviern (in der liste status auf 1 setzen)
    void oeffnen();            // alle schliessmotoren aktivieren (in der liste status auf 1 setzen)
    void lampe_an();
    void lampe_aus();
    void motoren_stopp();
};


#endif //TUERSTEUERUNG_CONFIG_H


