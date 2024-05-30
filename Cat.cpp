#include <iostream>
#include "Cat.h"

Cat::Cat(std::string petName) : Pet(petName), lives_(9){}
Cat::Cat():Pet(), lives_(9){}

int Cat::getLives(){ //+
    return lives_;
}

void Cat::setLives(int lives){ //+
    lives_ = lives;
}

bool Cat::death (){
    if (health_ <= 0 || rested_ <= 0 || satiated_ <= 0) {
        if (lives_ <= 0) {
            isAlive_ = false;
            return true;
        } else {
            health_ = 30;
            cleanliness_ = 30;
            rested_ = 30;
            satiated_ = 30;
            lives_--;
            return false;
        }
    }
    return false;
}

std::string Cat::getType(){
    return std::string("CAT"); 
}


