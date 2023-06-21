//
// Created by Justus Krenkel on 20.06.23.
//

#include "Config.h"
#include "DoorInterface.h"
#include <fstream>
#include <sstream>
#include <iostream>

Config::Config()
{

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
                s++;

            }
           z++;
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

