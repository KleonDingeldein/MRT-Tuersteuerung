//
// Created by Justus Krenkel on 20.06.23.
//

#include "Config.h"
#include "DoorInterface.h"
#include <fstream>
#include <sstream>
#include <iostream>

Config::Config(std::string datei)
{
    read(datei);
}

Config::~Config()
{

}

void Config::read(std::string filename)
{
    //log
    std::ofstream output;
    output.open("log.txt", std::ios_base::app);

    //std::string filename = "config.csv";
    std::ifstream input(filename); // lade Datei


    output << "...start config\n";

    if(input.is_open()) //Prüft ob Datei da ist, bzw. geöffnet werden kann.
    {
        std::string line;
        std::string delimiter = ",";


        int z = 0; //Zähler für die Zeilen

        //über alle Zeilen...
        while (std::getline(input, line))
        {
            std::stringstream linestream(line);
            std::string token;

            int s  = 0; //Zähler für die Spalten
            while(std::getline(linestream,token,','))
            {
              output << token << "\n";
                hardware_config[z][s]=output;
                s++;

            }
           z++;
        }
        // Erzeugung der Sensoren (Port 0 oder 1) und Aktoren (Port 2)
        int n = 0; 
        if(hardware_config[n][0]<2)
        {
            ArraySensor.pushback(Sensor(hardware_config[n][0],hardware_config[n][1],hardware_config[n][2],hardware_config[n][3],
            hardware_config[n][4],hardware_config[n][5])); 
            n++;   
        }
        else
        {   if(hardware_config[n][0]=2)
            {
            ArrayAktor.pushback(Aktor(hardware_config[n][0],hardware_config[n][1],hardware_config[n][2],hardware_config[n][3],
            hardware_config[n][4],hardware_config[n][5]));  
            }
            else{ output << "config konnte nicht übertragen werden\n"}
            n++;
        }
        /*
                //über alle elemente der liste

                //if aktor
                    //ArrayAktor.pushback(Aktor())

                //if sensor
                    Sensor tempSensor = Sensor()
                            //

        */
    }

    else
    {
        output << "config konnte nicht gefunden werden!!\n";
    }
    output << "...end config\n";
    output.close();
}

