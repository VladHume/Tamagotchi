#include "Dog.h"
#include <iostream>

Dog::Dog(std::string petName) : Pet(petName){}
Dog::Dog() : Pet(){}
bool Dog::death (){
    if (health_ <= 0 || fatigue_ <= 0 || hunger_ <= 0) {
            isAlive_ = false;
            return true;
        } else  return false;
}

std::string Dog::getType(){
    return std::string("DOG"); 
}
