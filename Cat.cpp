#include <iostream>
#include "Cat.h"

Cat::Cat(std::string petName) : Pet(petName), lives_(9){}

bool Cat::death (){
    if (health_ <= 0 || fatigue_ <= 0 || hunger_ <= 0) {
        if (lives_ <= 0) {
            isAlive_ = false;
            return true;
        } else {
            setHealth(30);
            setCleanliness(30);
            setFatigue(30);
            setHunger(30);
            lives_--;
            return false;
        }
    }
    return false;
}
