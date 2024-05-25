#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>

Player::Player(std::string name, Pet* pet): name_(name), pet_(pet), playerSteps_(0){}

int Player::countPlayerSteps(){
    return playerSteps_;
}

int Player::getSteps(){
    return playerSteps_;
}

void Player::setSteps(int playerSteps){
    playerSteps_ = playerSteps;
}