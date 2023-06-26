#include "Betriebsmode.h"
#include "Config.h"
#include <chrono>
#include <unistd.h>

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
    btype = newbtype;
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

void Betriebsmode::step(Config* conf) {
    if (condition==0 || condition==1 || condition==7 || condition==9){
        conf->motoren_stopp();
        //settype(3); //errorsituation automatishce betriebswahl 3 (aus)
    }

        //step fuer automatikbetrieb
    else if (btype==0){
        if(lasttype==0){
            //weiter im automatikmodus
            if (((condition!=10||condition!=3) && entrance==4) || (getDuration()>=3000)){
                //Timer stoppen
                conf->schliessen();
            }
            else if (condition==5 && (entrance!=0||entrance!=4)){
                //Timer starten
                startTimer();

            }
            else if ((( condition==2 || condition==5 || condition==8 ) && entrance==4)||(condition==8 && entrance==4)){
                conf->motoren_stopp();
            }
            else if ((( condition==2 || condition==4 || condition==5 || condition==6) && entrance==4)||(( condition==4 ||condition==6) && entrance==0)){
                conf->schliessen();
            }
            else if (condition!=5 && entrance!=4||(( condition==3 || condition==10 ) && entrance==4)){
                conf->oeffnen();
            }

        }
        else //zuvor nicht im automatikbetrieb gewesen
        {
            //automaikmodusstarten mit timer und so
            /*
             * usleep(5000*1000); //5s
             *
             */

            conf->lampe_an();
            usleep(5000*1000); //5s
            conf->lampe_aus();
        }
    }

    //step fuer handbetrieb
    else if (btype==1) {
        if ( (condition==2 && (entrance==0||entrance==2)) ||
             ((condition==4||condition==6) && (entrance==7||entrance==2||entrance==5)) ||
             (condition==5 && (entrance==0||entrance==2||entrance==5||entrance==7))||
             (condition==8 && (entrance==2||entrance==4)) ||
             (condition==4 && entrance==11)
            )
        {
            conf->motoren_stopp();
        }
        else if ( ((condition==2 || condition==4 || condition==5 || condition==6 ) && entrance==4)||((condition==4||condition==6) && entrance==1) ){
            conf->schliessen();
        }
        else if ( ((condition==4||condition==6) && (entrance==0||entrance==4||entrance==2||entrance==5||entrance==7))||((condition==2||condition==10) && (entrance==5||entrance==7)) ){
            conf->oeffnen();
        }
    }

    //step fuer reparaturbetrieb
    else if (btype==2) {
        if ((condition==5 && (entrance==1||entrance==2||entrance==5))||(condition==8 && entrance==4)||entrance==0||entrance==9){
            conf->motoren_stopp();
            conf->lampe_aus();
        }
        else if (condition!=8 && entrance==4){
            conf->lampe_an();
            conf->schliessen();
        }
        else if (condition!=5 && (entrance==1||entrance==2||entrance==5)){
            conf->lampe_an();
            conf->oeffnen();
        }
    }

}



