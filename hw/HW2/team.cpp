#include <iostream>
#include <iomanip>
#include "team.h"

//PURPOSE: Implementation file for the Team class
Team::Team(std::string aname){
    name = aname; 
    wins = 0;
    losses = 0;
    ties = 0;
    goals = 0;
    penalities = 0;   
}

std::string Team::getname() const {
    return name;
}

int Team::getwins() const {
    return wins;
}

int Team::getlosses() const {
    return losses;
}

int Team::getties() const {
    return ties;
}

double Team::get_win_percent() const{
    return (wins + 0.5 * ties) / (wins + losses + ties);
}

int Team::getgoals() const {
    return goals;
}

int Team::getpenalities() const {
    return penalities;
}

void Team::addwins(int i){
    wins += i;    
} 

void Team::addlosses(int i){
    losses += i;
}

void Team::addties(int i){
    ties += i;
}

void Team::addgoals(int i){
    goals += i;   
}

void Team::addpenalities(int i){
    penalities += i;
}
//compares the 2 team's by win% then by goals, then alphabetically
bool better(const Team& team1, const Team& team2){
    if (team1.get_win_percent() != team2.get_win_percent()){
        return (team1.get_win_percent() > team2.get_win_percent());
    } else if (team1.getgoals() != team2.getgoals()){
        return (team1.getgoals() > team2.getgoals());
    } else {
        return (team1.getname() < team2.getname());
    }
}