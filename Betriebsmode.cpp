#include "Betriebsmode.h"
#include <iostream>
#include <chrono>
#include <ctime>

// Constructor
Betriebsmode::Betriebsmode(unsigned int btype, unsigned int lasttype, unsigned int condition, unsigned int entrance) :
   condition(condition),
   entrance(entrance),
   btype(btype),
   lasttype(lasttype)
{

}

// Destructor
Betriebsmode::~Betriebsmode() = default;


void Betriebsmode::setentrance(int newEntrance)
{
    entrance = newEntrance;
}

void Betriebsmode::setcondition(int newCondition)
{
    condition = newCondition;
}

void Betriebsmode::setlasttype(int newlasttype) {
    lasttype = newlasttype;
}

void Betriebsmode::setbtype(int newbtype) {
    type = newbtype;
}

unsigned int Betriebsmode::getbtype(){
    return(btype);
}

void Betriebsmode::startTimer() {
    startTime = std::chrono::system_clock::now();
}

void Betriebsmode::stopTimer() {
    endTime = std::chrono::system_clock::now();
}

int Betriebsmode::getDuration() {
    endTime = std::chrono::system_clock::now();
    std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    return(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
}

void Betriebsmode::step() {
    if (condition==0 || condition==1 || condition==7 || condition==9){
        motoren_stopp();
        //settype(3); //errorsituation automatishce betriebswahl 3 (aus)
        break;
    }

        //step fuer automatikbetrieb
    if (type==0){
        if(lasttype==0){
            //weiter im automatikmodus
            if (((condition!=10||condition!=3) && entrance==4) || (getDuration()>=3000)){
                //Timer stoppen
                schliessen();
            }
            else if (condition==5 && (entrance!=0||entrance!=4)){
                //Timer starten
                startTimer();

            }
            else if ((( condition==2 || condition==5 || condition==8 ) && entrance==4)||(condition==8 && entrance==4)){
                motoren_stopp();
            }
            else if ((( condition==2 || condition==4 || condition==5 || condition==6) && entrance==4)||(( condition==4 ||condition==6) && entrance==0)){
                schliessen();
            }
            else if (condition!=5 && entrance!=4||(( condition==3 || condition==10 ) && entrance==4)){
                oeffnen();
            }

        }
        else //zuvor nicht im automatikbetrieb gewesen
        {
            //automaikmodusstarten mit timer und so
            /*
             * usleep(5000*1000); //5s
             *
             */

            lampe_an();
            usleep(5000*1000); //5s
            lampe_aus();
        }
    }

    //step fuer handbetrieb
    else if (type==1) {
        if ((condition==2 && (entrance==0||entrance==2))||((condition==4||condition==6) && (entrance==7||entrance==2||entrance==5))||(condition==5 && (entrance==0||entrance==2||entrance==5||entrance==7))||(condition==8 && (entrance==2||entrance==4))){
            motoren_stopp();
        }
        else if ( ((condition==2 || condition==4 || condition==5 || condition==6 ) && entrance==4)||((condition==4||condition==6) && entrance==1) ){
            schliessen();
        }
        else if ( ((condition==4||condition==6) && (entrance==0||entrance==4||entrance==2||entrance==5||entrance==7))||((condition==2||condition==10) && (entrance==5||entrance==7)) ){
            oeffnen();
        }
    }

    //step fuer reparaturbetrieb
    else if (type==2) {
        if ((condition==5 && (entrance==1||entrance==2||entrance==5))||(condition==8 && entrance==4)||entrance==0||entrance==9){
            motoren_stopp();
            lampe_aus();
        }
        else if (condition!=8 && entrance==4){
            lampe_an();
            schliessen();
        }
        else if (condition!=5 && (entrance==1||entrance==2||entrance==5)){
            lampe_an();
            oeffnen();
        }
    }

}



