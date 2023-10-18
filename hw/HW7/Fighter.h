#ifndef __FIGHTER_H__
#define __FIGHTER_H__
#include <iostream>
#include <string>

using uint = unsigned int;

//PURPOSE: deceleration of the Fighter class

class Fighter{
    public:
    //Constructor
    //Default constructor
    Fighter();
    Fighter(uint jab, uint ftilt, uint utilt, uint dtilt, uint fsmash, uint usmash, uint dsmash);

    //Accesors
    uint get_jab() const {return jab;}
    uint get_ftilt() const {return ftilt;}
    uint get_utilt() const {return utilt;}
    uint get_dtilt() const {return dtilt;}
    uint get_fsmash() const {return fsmash;}
    uint get_usmash() const {return usmash;}
    uint get_dsmash() const {return dsmash;}

    private:
    uint jab;
    uint ftilt;
    uint utilt;
    uint dtilt;
    uint fsmash;
    uint usmash;
    uint dsmash;
    
};
#endif