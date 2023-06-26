#ifndef TUERSTEUERUNG_BETRIEBSMODE_H
#define TUERSTEUERUNG_BETRIEBSMODE_H

#include <iostream>
#include <chrono>
#include <ctime>
#include "Config.h"

class Betriebsmode {
private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
    std::chrono::time_point<std::chrono::system_clock> endTime;


public:
    Betriebsmode(unsigned int btype, unsigned int lasttype, unsigned int condition, unsigned int entrance);  //Constructor
    ~Betriebsmode();    //Destructor

    void setcondition(int newCondition);
    void setentrance(int newEntrance);
    void setlasttype(int newlasttype);
    void setbtype(int newbtype);
    unsigned int getbtype();
    void step(Config* conf);
    void startTimer();
    void stopTimer();
    int getDuration();


protected:
    unsigned int condition;
    unsigned int entrance;
    unsigned int btype;
    unsigned int lasttype;

};


#endif //TUERSTEUERUNG_BETRIEBSMODE_H