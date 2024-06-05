#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>

//constructors
Player::Player(std::string name, Pet* pet, int playerSteps): name_(name), pet_(pet), playerSteps_(playerSteps), timeInGame_("00:00:00"), timePhase_("РАНОК") {}
Player::Player(): name_(""), pet_(nullptr), playerSteps_(0), timeInGame_("00:00:00"), timePhase_("РАНОК") {}

//destructor
Player::~Player(){
    delete pet_;
}

//method for increase player steps in game
void Player::increasePlayerSteps(){
    if(pet_->getIsAlive()){
        ++playerSteps_;
    }
}

//getters
int Player::getSteps(){
    return playerSteps_;
}

std::string Player::getName(){
    return name_;
}

std::string Player::getTimeInGame(){
     return timeInGame_;
}

Pet* Player::getPet(){
    return pet_;
}

std::string Player::getTimePhase(){
    return timePhase_;
}
      
//setters
void Player::setName(std::string name){
    name_ = name;
}

void Player::setSteps(int playerSteps){
    playerSteps_ = playerSteps;
}

void Player::setTimePhase(std::string timePhase)
{
    timePhase_ = timePhase; 
}


void Player::setTimeInGame(std::string timeInGame)
{
    timeInGame_ = timeInGame;
}

void Player::setPet(Pet* pet) {
    pet_ = pet;
}
