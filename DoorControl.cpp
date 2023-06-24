* Praktikum MRT2 
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r2
 */

#include "DoorInterface.h"
#include "DoorControl.h"
#include "Config.h"
#include "Textausgabe.h"





DoorControl::DoorControl() : door_if(false, true)
{
	// constructor
	// ... maybe, insert your sensor and actor initialization here?
}

DoorControl::~DoorControl()
{
	// destructor
	door_if.quit_doorcontrol_flag = true;
}

void DoorControl::run()
{

    // Erstelle Objekt der Klasse config welches auf Basis der config.txt gebaut wird
	Config steuerung("config.txt");




	// Hauptschleife:
	while(1) {
		// Betriebswahl Automatikbetrieb if(BW1 && BW2)
		// automatikbetrieb()

		// Betriebswahl Handbetrieb if(...)
		// handbetrieb()

		// Betriebswahl Reparatur if(...)
		// reparatur()

		// Aus ...
		// aus()

	}
}
