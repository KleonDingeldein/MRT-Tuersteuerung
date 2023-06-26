/*
 * Praktikum MRT2 
 * ART1 Türsteuerung
 * Institut für Automatisierungstechnik
 * letztes Update Mai 2018
 * Autor: M.Herhold
 * Version: r2
 */

#include "DoorInterface.h"
#include "DoorControl.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

DoorControl::DoorControl() :
    door_if(false, true),
    confReader()

{
	// constructor
	// ... maybe, insert your sensor and actor initialization here?

    //log
    std::ofstream output;
    output.open("log.txt");
    output << "----start----\n";
    output.close();

    confReader.read("config.csv");

}

DoorControl::~DoorControl()
{
	// destructor
	door_if.quit_doorcontrol_flag = true;

    std::ofstream output;
    output.open("log.txt", std::ios_base::app);
    output << "----ende----\n";
    output.close();

}
//main loop in here
void DoorControl::run()
{
	std::string msg;		// temporary variable to construct message

    /*
    //Test fuer Aktorupdatefunktion wirteHardware
    confReader.aktoren.at(0) = new Aktor(2,0,"Akt1",1);
    confReader.aktoren.at(1) = new Aktor(2,1,"Akt2",1);
    confReader.aktoren.at(2) = new Aktor(2,2,"Akt3",0);

    writeHardware();
     */

    //erstellen des laufbetriebs
    betrieb = new Betriebsmode(0,1,0,0);


    //main loop
    while(!door_if.quit_doorcontrol_flag)
    {
        readHardware(); //auslesen/updaten der sensorenliste

        //Beginn Unterscheidung der Betriebswahl
        if (betriebswahl()==0) //0 Automatikbetrieb
        {
            betrieb.settype(0);
            betrieb.setcondition(buildcondition());
            betrieb.setentrance(buildentrance());

            betrieb.step();

            betrieb.setlasttype(0);
            writeHardware(); //updaten der aktorenpins

        }
        else if (betriebswahl()==1) //1 Handbetrieb
        {
            betrieb.settype(1);
            betrieb.setcondition(buildcondition());
            betrieb.setentrance(buildentrance());

            betrieb.step();

            betrieb.setlasttype(1);
            writeHardware(); //updaten der aktorenpins

        }
        else if (betriebswahl()==2) //2 Reparatur
        {
            betrieb.settype(2);
            betrieb.setcondition(buildcondition());
            betrieb.setentrance(buildentrance());

            betrieb.step();

            betrieb.setlasttype(2);
            writeHardware(); //updaten der aktorenpins

        }
        else if (betriebswahl()==3) //3 Aus
        {
            for (int i = 0; i < 8; ++i)  //Schleife um alle Aktoren 0 zusetzen
            {
                confReader.aktoren.at(i)->setStatus(0);
            };
            writeHardware(); //updaten der aktoren
            lastBM = 3;
        }

		//construct counter message
		msg = "press 'q'";

		// set current message to be displayed by user interface
		door_if.DebugString(msg);

	}
}

void DoorControl::readHardware() {

    // x & 1 - Bit-Operator: Vergleicht das letze signifikate bit von x mit 1. Bei 1 -> 1 bei 0 -> 0
    door_if.DIO_Read(0, &pins_port_0);
    door_if.DIO_Read(1, &pins_port_1);

    //Aktualisierung des Status der Sensoren
    for(int i = 0; i < (confReader.senoren.size() -1); i++)
    {
        if (i<8)
        {
            confReader.senoren.at(i)->setStatus((pins_port_0 >> i) & 1);
        }
        else
        {
            confReader.senoren.at(i)->setStatus((pins_port_1 >> (i - 8)) & 1);
        }
    }
}

void DoorControl::writeHardware() {

    for(int i = 0 ; i < confReader.aktoren.size(); i++)
    {
        pins_port_2 = (confReader.aktoren.at(i)->getStatus() << (8-i));
    }
    if (pins_port_2 && "110")
    {
        std::ofstream output;
        output.open("log.txt");
        output << "passt\n";
        output.close();
    }

    door_if.DIO_Write(2,pins_port_2);

}

int DoorControl::buildcondition() //codiert endlagenstatus und aktorstatus in automatenzustaende
{
    /* Codierung der Automatenzustaende
     * 0 Motoren für oeffnen und schliessen gleichzeitig aktiv
     * 1 Beide Endlagen gleichzeitig erreicht
     * 2 zwischen den Endlagen, Motoren aus
     * 3 zwischen den Endlagen, oeffnet
     * 4 zwischen den Endlagen, schliesst
     * 5 Endlageoffen, Motoren aus
     * 6 Endlageoffen, schliesst
     * 7 Endlageoffen, oeffnet
     * 8 Endlagegeschlossen, Motorenaus
     * 9 Endlagegeschlossen, schliesst
     * 10 Endlagegeschlossen, oeffnet
     */
    if (  oeffnet() && schliesst()  ){
        return(0);
    }
    else if ( endlage_offen() && entlage_geschlossen() ) {
        return(1);
    }
    else if (!endlage_offen() && !entlage_geschlossen() && !oeffnet() && !schliesst() ) {
        return(2);
    }
    else if (!endlage_offen() && !entlage_geschlossen() && oeffnet() && !schliesst() ) {
        return(3);
    }
    else if ( !endlage_offen() && !entlage_geschlossen() && !oeffnet() && schliesst() ) {
        return(4);
    }
    else if (endlage_offen() && !entlage_geschlossen() && !oeffnet() && schliesst() ) {
        return(5);
    }
    else if (endlage_offen() && !entlage_geschlossen() && !oeffnet() && schliesst() ) {
        return(6);
    }
    else if (endlage_offen() && !entlage_geschlossen() && oeffnet() && !schliesst() ) {
        return(7);
    }
    else if (!endlage_offen() && entlage_geschlossen() && !oeffnet() && !schliesst() ) {
        return(8);
    }
    else if (!endlage_offen() && entlage_geschlossen() && !oeffnet() && schliesst() ) {
        return(9);
    }
    else if (!endlage_offen() && entlage_geschlossen() && oeffnet() && !schliesst() ) {
        return(10);
    }
}

int DoorControl::buildentrance() //codiert sensorstatus in uebergangsbedingungen
{
    /* Codierung der Uebergangsbedingungen
     * 0 kein Sensor aktiv
     * 1 nur Person vor Tuer
     * 2 nur Person in Tuer
     * 3 nur Person in und vor Tuer
     * 4 nur manuelles schliessen
     * 5 nur manuelles oeffnen
     * 6 nur manuelles oeffnen und Person vor Tuer
     * 7 nur manuelles oeffnen und Person in Tuer
     * 8 nur manuelles oeffnen und Person in Tuer und Person vor Tuer
     * 9 mehrere Sensoren aktiv nur fuer reparaturbetrieb
     * 10 manuelles oeffnen oder Person in Tuer oder Person vor Tuer nur fuer automatik
     *
     */
    if ( (betrieb.gettype() == 2) && mehrere_sensoren_aktiv()){
        return(9);
    } else

    if (!manuelles_oeffnen() && !manuelles_schliessen() && !pesron_in_tuer() && !person_vor_tuer() ){
        return(0);
    }
    else if (!manuelles_oeffnen() && !manuelles_schliessen() && !pesron_in_tuer() && person_vor_tuer()) {
        return(1);
    }
    else if (!manuelles_oeffnen() && !manuelles_schliessen() && pesron_in_tuer() && !person_vor_tuer()) {
        return(2);
    }
    else if (!manuelles_oeffnen() && !manuelles_schliessen() && pesron_in_tuer() && person_vor_tuer()) {
        return(3);
    }
    else if (!manuelles_oeffnen() && manuelles_schliessen() && !pesron_in_tuer() && !person_vor_tuer()) {
        return(4);
    }
    else if (manuelles_oeffnen() && !manuelles_schliessen() && !pesron_in_tuer() && !person_vor_tuer()) {
        return(5);
    }
    else if (manuelles_oeffnen() && !manuelles_schliessen() && !pesron_in_tuer() && person_vor_tuer()) {
        return(6);
    }
    else if (manuelles_oeffnen() && !manuelles_schliessen() && pesron_in_tuer() && !person_vor_tuer()) {
        return(7);
    }
    else if (manuelles_oeffnen() && !manuelles_schliessen() && pesron_in_tuer() && person_vor_tuer()) {
        return(8);
    }
    else if (manuelles_oeffnen() || pesron_in_tuer() || person_vor_tuer()) {
        return(10);
    }

}
