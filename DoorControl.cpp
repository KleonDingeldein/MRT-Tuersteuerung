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
    betrieb(0,3,0,0)
{
	// constructor
	// ... maybe, insert your sensor and actor initialization here?
}

DoorControl::~DoorControl() {
    // destructor
    writeLog("---Stop DoorControl run---");
    writeLog("");
    door_if.quit_doorcontrol_flag = true;

}

void DoorControl::run()
{
	// ... insert your main loop here ...
	// example:

    writeLog("---Start DoorControl run---");
	std::string msg;		// temporary variable to construct message

    Config *confReader = new Config("config.txt");

    //erstellen des laufbetriebs
    //Betriebsmode betrieb = *new Betriebsmode(0,1,0,0);

    /*writeHardware(confReader);
    confReader->aktoren.at(1).setStatus(0);
    writeHardware(confReader);*/

    //main loop
    while(!door_if.quit_doorcontrol_flag)
    {

        readHardware(confReader); //auslesen/updaten der sensorenliste

        //Beginn Unterscheidung der Betriebswahl
        if (confReader->betriebswahl()==0) //0 Automatikbetrieb
        {
            betrieb.setbtype(0);
            betrieb.setcondition(buildcondition(confReader));
            betrieb.setentrance(buildentrance(confReader));

            betrieb.step(confReader);

            betrieb.setlasttype(0);
            writeHardware(confReader); //updaten der aktorenpins

        }
        else if (confReader->betriebswahl()==1) //1 Handbetrieb
        {
            betrieb.setbtype(1);
            betrieb.setcondition(buildcondition(confReader));
            writeLog("condition: " + std::to_string(buildcondition(confReader)));
            betrieb.setentrance(buildentrance(confReader));
            writeLog("entrance: " + std::to_string(buildentrance(confReader)));
            betrieb.step(confReader);

            betrieb.setlasttype(1);
            writeHardware(confReader); //updaten der aktorenpins

        }
        else if (confReader->betriebswahl()==2) //2 Reparatur
        {
            betrieb.setbtype(2);
            betrieb.setcondition(buildcondition(confReader));
            betrieb.setentrance(buildentrance(confReader));

            betrieb.step(confReader);

            betrieb.setlasttype(2);
            writeHardware(confReader); //updaten der aktorenpins

        }
        else if (confReader->betriebswahl()==3) //3 Aus
        {
            confReader->motoren_stopp();
            writeHardware(confReader); //updaten der aktoren
        }
        //construct counter message
        msg = "press 'q'";

        // set current message to be displayed by user interface
        door_if.DebugString(msg);

    }
}

void DoorControl::readHardware(Config *conf) {

    // x & 1 - Bit-Operator: Vergleicht das letze signifikate bit von x mit 1. Bei 1 -> 1 bei 0 -> 0
    door_if.DIO_Read(0, &pins_port_0);
    door_if.DIO_Read(1, &pins_port_1);


    //writeLog("Port: 0 - Pins: " + std::to_string(pins_port_0));
    //writeLog("Port: 1 - Pins: " + std::to_string(pins_port_1));

    //Aktualisierung des Status der Sensoren
    for(int i = 0; i < (conf->sensoren.size() - 1); i++)
    {
        if (i<8)
        {
            writeLog(std::to_string(((pins_port_0>>i) & 1)) ,1);
            conf->sensoren.at(i).setStatus((pins_port_0 >> i) & 1);

        }
        else
        {
            writeLog(std::to_string(((pins_port_1 >> (i - 8)) & 1)) ,1);
            conf->sensoren.at(i).setStatus((pins_port_1 >> (i - 8)) & 1);
        }
    }
    writeLog("");
}

void DoorControl::writeHardware(Config *conf) {
    pins_port_2 = 0;

    for(int i = 0 ; i < (conf->aktoren.size()); i++)
    {
        //writeLog(std::to_string(conf->aktoren.at(i).getStatus()),true);
        pins_port_2 |= (conf->aktoren.at(i).getStatus()<<i);
    }
    //writeLog("Port: 2 - Pins: " + std::to_string(pins_port_2));
    door_if.DIO_Write(2,pins_port_2);

}

void DoorControl::writeLog(std::string sLog, bool noNewLine) {

    //Logeintrag ohne Zeilenumbruch
    if (noNewLine) {
        std::ofstream output;
        output.open("log.txt", std::ios_base::app);
        output << sLog;
        output.close();
    }
    //Logeintrag mit Zeilenumbruch
    else{
        std::ofstream output;
        output.open("log.txt", std::ios_base::app);
        output << sLog << "\n";
        output.close();
    }
}

int DoorControl::buildcondition(Config *confReader) //codiert endlagenstatus und aktorstatus in automatenzustaende
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
    if ( confReader->oeffnet() && confReader->schliesst()  ){
        return(0);
    }
    else if ( confReader->endlage_offen() && confReader->endlage_geschlossen() ) {
        return(1);
    }
    else if (!(confReader->endlage_offen()) && !(confReader->endlage_geschlossen()) && !(confReader->oeffnet()) && !(confReader->schliesst()) ) {
        return(2);
    }
    else if (!(confReader->endlage_offen()) && !(confReader->endlage_geschlossen()) && confReader->oeffnet() && !(confReader->schliesst()) ) {
        return(3);
    }
    else if ( !(confReader->endlage_offen()) && !(confReader->endlage_geschlossen()) && !(confReader->oeffnet()) && confReader->schliesst() ) {
        return(4);
    }
    else if (confReader->endlage_offen() && !(confReader->endlage_geschlossen()) && !(confReader->oeffnet()) && confReader->schliesst() ) {
        return(5);
    }
    else if (confReader->endlage_offen() && !(confReader->endlage_geschlossen()) && !(confReader->oeffnet()) && confReader->schliesst() ) {
        return(6);
    }
    else if (confReader->endlage_offen() && !(confReader->endlage_geschlossen()) && confReader->oeffnet() && !(confReader->schliesst()) ) {
        return(7);
    }
    else if (!(confReader->endlage_offen()) && confReader->endlage_geschlossen() && !(confReader->oeffnet()) && !(confReader->schliesst()) ) {
        return(8);
    }
    else if (!(confReader->endlage_offen()) && confReader->endlage_geschlossen() && !(confReader->oeffnet()) && confReader->schliesst() ) {
        return(9);
    }
    else if (!(confReader->endlage_offen()) && confReader->endlage_geschlossen() && confReader->oeffnet() && !(confReader->schliesst()) ) {
        return(10);
    }
}

int DoorControl::buildentrance(Config *confReader) //codiert sensorstatus in uebergangsbedingungen
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
     * 11 manuelles schließen stoppen durch Einklemmschutz
     */

    if ( (betrieb.getbtype() == 2) && confReader->mehrere_sensoren_aktiv()){
        return(9);
    } else

    if (!(confReader->manuelles_oeffnen()) && !(confReader->manuelles_schliessen()) && !(confReader->person_in_tuer()) && !(confReader->person_vor_tuer()) ){
        return(0);
    }
    else if (!(confReader->manuelles_oeffnen()) && !(confReader->manuelles_schliessen()) && !(confReader->person_in_tuer()) && confReader->person_vor_tuer() ) {
        return(1);
    }
    else if (!(confReader->manuelles_oeffnen()) && !(confReader->manuelles_schliessen()) && confReader->person_in_tuer() && !(confReader->person_vor_tuer()) ) {
        return(2);
    }
    else if (!(confReader->manuelles_oeffnen()) && !(confReader->manuelles_schliessen()) && confReader->person_in_tuer() && confReader->person_vor_tuer()) {
        return(3);
    }
    else if (  confReader->person_in_tuer() && confReader->manuelles_schliessen() ) {
        return(11);
    }

    else if (!(confReader->manuelles_oeffnen()) &&
            confReader->manuelles_schliessen() &&
            !(confReader->person_in_tuer()) &&
            !(confReader->person_vor_tuer())
            ) {
        writeLog("Status LSH: " + std::to_string(confReader->sensoren.at(7).getStatus()));
        return(4);
    }



    else if ( (confReader->manuelles_oeffnen() || confReader->person_in_tuer()) && confReader->manuelles_schliessen() ) {
        return(11);
    }
    else if (confReader->manuelles_oeffnen() && !(confReader->manuelles_schliessen()) && !(confReader->person_in_tuer()) && !(confReader->person_vor_tuer()) ) {
        return(5);
    }
    else if (confReader->manuelles_oeffnen() && !(confReader->manuelles_schliessen()) && !(confReader->person_in_tuer()) && confReader->person_vor_tuer() ) {
        return(6);
    }
    else if (confReader->manuelles_oeffnen() && !(confReader->manuelles_schliessen()) && confReader->person_in_tuer() && !(confReader->person_vor_tuer()) ) {
        return(7);
    }
    else if (confReader->manuelles_oeffnen() && !(confReader->manuelles_schliessen()) && confReader->person_in_tuer() && confReader->person_vor_tuer() ) {
        return(8);
    }
    else if (confReader->manuelles_oeffnen() || confReader->person_in_tuer() || confReader->person_vor_tuer()) {
        return(10);
    }

}
