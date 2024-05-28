#include "Pet.h"
#include "Player.h"
#include <iostream>
#include <cstring>
#include <string>


Pet::Pet(std::string petName): attention_(60), health_(100), cleanliness_(60), fatigue_(90), hunger_(60), name_(petName), isAlive_(true){}


virtual bool Pet::death() = 0;


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
