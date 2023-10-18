#include <iostream>
#include "Fighter.h"

//PURPOSE: Implemetation of the Fighter class

using str = std::string;
using uint = unsigned int;

//Default Constructor
Fighter::Fighter(){
    jab = 0;
    ftilt = 0;
    utilt = 0;
    dtilt = 0;
    fsmash = 0;
    usmash = 0;
    dsmash = 0;
}

//Constructor
Fighter::Fighter(uint ajab, uint aftilt, uint autilt, uint adtilt, 
                 uint afsmash, uint ausmash, uint adsmash){
    jab = ajab;
    ftilt = aftilt;
    utilt = autilt;
    dtilt = adtilt;
    fsmash = afsmash;
    usmash = ausmash;
    dsmash = adsmash;
}