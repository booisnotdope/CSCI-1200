// File:    Time.cpp
// Purpose: Implementation file for the Time class.

#include <iostream>
#include "time.h"

// array to figure out the number of secss, it's used by the auxiliary function secssInmins
const int secssInmins[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Time::Time() {	//default constructor
  secs = 0;
  mins = 0;
  hours = 0;
}

Time::Time(int ahours, int amins, int asecs) { // construct from mins, secs, & hours
  hours = ahours;
  mins = amins;
  secs = asecs;
}


int Time::getSecond() const {
  return secs;
}

int Time::getMinute() const {
  return mins;
}
	
int Time::getHour() const {
  return hours;
}

void Time::setSecond(int s) {
  secs = s;
}

void Time::setMinute(int m) {
  mins = m;
}

void Time::setHour(int h) {
  hours = h; 
}

void Time::PrintAMPM() {
  if (hours > 12){
    std::cout << hours - 12 << ':' << mins << ':' << secs << "pm" << std::endl;
  } else if (hours == 0) {
    std::cout << hours + 12 << ':' << mins << ':' << secs << "am" << std::endl;
  } else if (hours == 12) {
    std::cout << hours << ':' << mins << ':' << secs << "pm" << std::endl;

  } else {
    std::cout << hours << ':' << mins << ':' << secs << "am" << std::endl;
  }
}

bool IsEarlierThan(const Time& t1, const Time& t2){
  if (t1.getHour() < t2.getHour()){
    return true;
  } else if (t1.getHour() > t2.getHour()){
    return false;
  } else {
    if (t1.getMinute() < t2.getMinute()){
      return true;
    } else if (t1.getMinute() > t2.getMinute()){
      return false;
    } else {
      if (t1.getSecond() < t2.getSecond()){
        return true;
      } else {
        return false;
      }
    }
  }
}
