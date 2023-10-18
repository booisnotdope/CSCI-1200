#include <iostream>
#include <iomanip>
#include "player.h"

//PURPOSE: Implementaion of the Player class.
Player::Player(std::string aplayer, std::string ateam){
    player = aplayer;
    team = ateam;
    goals = 0;
    assists = 0;
    penalities = 0;
}

std::string Player::getplayer() const{
    return player;
}

std::string Player::getteam() const{
    return team;
}

int Player::getgoals() const{
    return goals;
}

int Player::getassists() const{
    return assists;
}

int Player::getpenalities() const{
    return penalities;
}

void Player::addgoals(int i){
    goals += i;
}

void Player::addassists(int i){
    assists += i;
}

void Player::addpenalities(int i){
    penalities += i;
}
//compares 2 players goals and assists, least penalities, then 
bool stronger(const Player& player1, const Player& player2){
    int player1_stats = player1.getgoals() + player1.getassists();
    int player2_stats = player2.getgoals() + player2.getassists();
    if (player1_stats != player2_stats) {
        return (player1_stats > player2_stats);
    } else if (player1.getpenalities() != player2.getpenalities()){
        return (player1.getpenalities() < player2.getpenalities());
    } else {
        return (player1.getplayer() < player2.getplayer());
    }
}