#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>
//змінила орядок оголошення в конструкторі
Player::Player(std::string name, Pet* pet, int playerSteps): name_(name), pet_(pet), playerSteps_(playerSteps){}
Player::Player(): name_(""), pet_(nullptr), playerSteps_(0){}

Player::~Player(){
    delete pet_;
}

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
    name_ = name;
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
