#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>

Player::Player(std::string name, Pet* pet, int playerSteps): name_(name), pet_(pet), playerSteps_(playerSteps){}
Player::Player(): name_("\0"), pet_(nullptr), playerSteps_(0){}

void Player::increasePlayerSteps(){
    ++playerSteps_;
}

int Player::getSteps(){
    return playerSteps_;
}

std::string Player::getName(){
    return name_;
}

void Player::setName(std::string name){
    strcpy(name_, name);
}

void Player::setSteps(int playerSteps){
    playerSteps_ = playerSteps;
}

Pet* Player::getPet(){
    return pet_;
}

void Player::setPet(Pet* pet) {
    pet_ = pet;
}
