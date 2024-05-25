#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>

Player::Player(std::string name, Pet* pet): name_(name), pet_(pet), playerSteps_(0){}

Player::countPlayerSteps(){
    return playerSteps_;
}

Player::getSteps(){
    return playerSteps_;
}

Player::setSteps(int playerSteps){
    playerSteps_ = playerSteps;
}