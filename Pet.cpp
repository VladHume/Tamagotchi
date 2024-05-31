#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>


Pet::Pet(std::string name): attention_(60), health_(100), cleanliness_(60), rested_(90), satiated_(60), name_(name), isAlive_(true), currentMood_(MOOD::NORMAL){}

Pet::Pet(): attention_(0), health_(0), cleanliness_(0), rested_(0), satiated_(0), name_(""), isAlive_(true), currentMood_(MOOD::NORMAL){}

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

int Pet::getRested(){
    return rested_;
}

int Pet::getSatiated(){
    return satiated_;
}

std::string Pet::getName(){
        return name_;
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
void Pet::setRested(int rested){
    rested_ = rested;
}
void Pet::setSatiated(int satiated){
    satiated_ = satiated;
}

void Pet::setName(std::string name){
    name_ = name;
}

void Pet::setMood(MOOD mood){  //+
    currentMood_ = mood;
}


void Pet::feed() {
     if (isAlive_) {
        satiated_ += 20;
        if (satiated_ > 100)
            satiated_ = 100;
        cleanliness_ -= 10;
        rested_ -= 10;
        health_ += 5;
        if (health_ > 100)
            health_ = 100;
     }
}

   
void Pet::treat(){
      if (isAlive_) {
        if(health_ < 90){
            health_ = 100;
            rested_ -= 10;
        }
    }
}


void Pet::clean() {
     if (isAlive_) {
        cleanliness_ += 30;
        if (cleanliness_ > 100)
            cleanliness_ = 100;
        rested_ -= 10;
    }
}


void Pet::play(){
    if (isAlive_) {
        attention_ += 20;
        if (attention_ > 100)
            attention_ = 100;
        cleanliness_ -= 10;
        satiated_ -= 10;
        rested_ -= 20;
    }
}


void Pet::pet() {
    if (isAlive_) {
        attention_ += 10;
        if (attention_ > 100)
            attention_ = 100;
        cleanliness_ -= 5;
        satiated_ -= 5;
        rested_ -= 5;
    }
}


void Pet::punch(){
     if (isAlive_) {
        health_ -= 10;
        rested_ -= 10;
    } 
}


void Pet::goToSleep() {
    if (isAlive_) {
        if(rested_ < 100){
            rested_ = 100;
            satiated_ -= 20;
        }
    } 
}


void Pet::checkMood(){
    double generalMood = ((attention_ *0.8)+ health_ + rested_*0.8 + satiated_ + (cleanliness_*0.5)) / 5;
    if(generalMood >= 80 && generalMood <= 100){
        currentMood_ = MOOD::HAPPY;
    }else if(generalMood >= 50 && generalMood < 80){
        currentMood_ = MOOD::NORMAL;
    }else{
        currentMood_ = MOOD::SAD;
    }
}

