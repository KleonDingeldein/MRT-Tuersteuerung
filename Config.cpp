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

    std::string filename = "config.csv";
    std::ifstream input(filename); // lade Datei


    output << "...start config\n";
    std::vektor <std::string> gelesen;

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
                gelesen.push_back(token);
                s++;
            }
            // Zeilenweise erstellung von Sensor/Aktor je nach Port
            unsigned int port = atoi(gelesen[0]);
            unsigned int pin = atoi(gelesen[1]);
            std::string funktion = gelesen[2];
            unsigned int status = atoi(gelesen[3]);
            unsigned int activation = atoi(gelesen[4]);
            gelesen.clear();
            switch (port)
            {
                case '0': sensorliste.emplace_back(port,pin,funktion,status,activation);
                break;
                case '1': sensorliste.emplace_back(port,pin,funktion,status,activation);
                break;
                case '2': aktorliste.emplace_back(Aktor(port,pin,funktion,status,activation));
                break;
                default:
                    break;
            }
           z++;
        }
    }

    else
    {
        output << "config konnte nicht gefunden werden!!\n";
    }
    output << "...end config\n";
    output.close();
}

