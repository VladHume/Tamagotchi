#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>


Pet::Pet(std::string petName): attention_(60), health_(100), cleanliness_(60), fatigue_(90), hunger_(60), name_(petName), isAlive_(true){}

Pet::Pet(): attention_(0), health_(0), cleanliness_(0), fatigue_(0), hunger_(0), name_('\0'), isAlive_(true){}

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

std::string Pet::getName(){
        return name_;
}
bool Pet::getIsAlive(){
    return isAlive_;
}

//MOOD Pet::getMood(){
//   return MOOD.currentMood_;
//}


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

void Pet::setName(std::string name){
    name_ = name;
}

//void Pet::setMood(MOOD mood){
//    MOOD.currentMood_ = mood;
//}


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


