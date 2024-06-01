#include "Dog.h"
#include <iostream>

Dog::Dog(std::string name) : Pet(name, FileUtility::readFrames(happyPath),  FileUtility::readFrames(sadPath), FileUtility::readFrames(usualPath), FileUtility::readFrames(sleepPath), FileUtility::readFrames(deathPath)) {}
Dog::Dog() : Pet(){}
bool Dog::death (){
    if (health_ <= 0 || rested_ <= 0 || satiated_ <= 0) {
            isAlive_ = false;
            return true;
        } else  return false;
}

std::string Dog::getType(){
    return std::string("DOG"); 
}
