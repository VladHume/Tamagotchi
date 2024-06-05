#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>
//змінила орядок оголошення в конструкторі
Player::Player(std::string name, Pet* pet, int playerSteps): name_(name), pet_(pet), playerSteps_(playerSteps), timeInGame_(""), timePhase_(""){}
Player::Player(): name_(""), pet_(nullptr), playerSteps_(0), timeInGame_(""), timePhase_("") {}

Player::~Player(){
    delete pet_;
}

void Player::increasePlayerSteps(){
    if(pet_->getIsAlive()){
        ++playerSteps_;
    }
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

void Player::setTimePhase(std::string timePhase)
{
    timePhase_ = timePhase; 
}

std::string Player::getTimeInGame()
{
    return timeInGame_;
}

void Player::setTimeInGame(std::string timeInGame)
{
    timeInGame_ = timeInGame;
}

Pet* Player::getPet(){
    return pet_;
}

void Player::setPet(Pet* pet) {
    pet_ = pet;
}

std::string Player::getTimePhase()
{
    return timePhase_;
}
