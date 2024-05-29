#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>


Pet::Pet(std::string petName): attention_(60), health_(100), cleanliness_(60), fatigue_(90), hunger_(60), petName_(petName), isAlive_(true), currentMood_(MOOD::NORMAL){}

Pet::Pet(): attention_(0), health_(0), cleanliness_(0), fatigue_(0), hunger_(0), petName_(""), isAlive_(true), currentMood_(MOOD::NORMAL){}

//гетери
int  Pet::getAttention(){
    return attention_;
}
int Pet::getHealth(){
    return health_;
}
 int Pet::getCleanliness(){
    return cleanliness_;
 }

int Pet::getFatigue(){
    return fatigue_;
}

int Pet::getHunger(){
    return hunger_;
}

std::string Pet::getPetName(){
        return petName_;
}
bool Pet::getIsAlive(){
    return isAlive_;
}

MOOD Pet::getMood(){  //+
  return currentMood_;
}


//сетери
void Pet::setIsAlive(bool isAlive){
    isAlive_ = isAlive;
}

void Pet::setAttention(int attention){
    attention_ = attention;
}
void Pet::setHealth(int health){
    health_ = health;
}
void Pet::setCleanliness(int cleanliness){
    cleanliness_ = cleanliness;
}
void Pet::setFatigue(int fatigue){
    fatigue_ = fatigue;
}
void Pet::setHunger(int hunger){
    hunger_ = hunger;
}

void Pet::setPetName(std::string petName){
    petName_ = petName;
}

void Pet::setMood(MOOD mood){  //+
    currentMood_ = mood;
}


void Pet::feed() {
     if (isAlive_) {
        hunger_ += 20;
        if (hunger_ > 100)
            hunger_ = 100;
        cleanliness_ -= 10;
        fatigue_ -= 10;
        health_ += 5;
        if (health_ > 100)
            health_ = 100;
     }
}

   
void Pet::treat(){
      if (isAlive_) {
        if(health_ < 90){
            health_ = 100;
            fatigue_ -= 10;
        }
    }
}


void Pet::clean() {
     if (isAlive_) {
        cleanliness_ += 30;
        if (cleanliness_ > 100)
            cleanliness_ = 100;
        fatigue_ -= 10;
    }
}


void Pet::play(){
    if (isAlive_) {
        attention_ += 20;
        if (attention_ > 100)
            attention_ = 100;
        cleanliness_ -= 10;
        hunger_ -= 10;
        fatigue_ -= 20;
    }
}


void Pet::pet() {
    if (isAlive_) {
        attention_ += 10;
        if (attention_ > 100)
            attention_ = 100;
        cleanliness_ -= 5;
        hunger_ -= 5;
        fatigue_ -= 5;
    }
}


void Pet::punch(){
     if (isAlive_) {
        health_ -= 10;
        fatigue_ -= 10;
    } 
}


void Pet::goToSleep() {
    if (isAlive_) {
        if(fatigue_ < 100){
            fatigue_ = 100;
            hunger_ -= 20;
        }
    } 
}


void Pet::checkMood(){
    double generalMood = ((attention_ *0.8)+ health_ + fatigue_*0.8 + hunger_ + (cleanliness_*0.5)) / 5;
    if(generalMood >= 80 && generalMood <= 100){
        currentMood_ = MOOD::HAPPY;
    }else if(generalMood >= 50 && generalMood < 80){
        currentMood_ = MOOD::NORMAL;
    }else{
        currentMood_ = MOOD::SAD;
    }
}

