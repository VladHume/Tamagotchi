#ifndef DOG_H
#define DOG_H

#include <iostream>
#include "Pet.h"
#include <cstring>
#include <string>

class Dog : public Pet{
    public:   
    Dog(std::string name);  
    Dog();   
    bool death() override;
    std::string getType() override; 
};

#endif
