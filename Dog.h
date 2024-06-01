#ifndef DOG_H
#define DOG_H

#include <iostream>
#include "Pet.h"
#include "FileUtility.h"
#include <string>

class Dog : public Pet{
    const std::string happyPath = "pictures\\pet\\dog\\happyDog";
    const std::string sadPath = "pictures\\pet\\dog\\sadDog";
    const std::string sleepPath = "pictures\\pet\\dog\\sleepDog";
    const std::string deathPath = "pictures\\pet\\dog\\deathDog";
    const std::string usualPath = "pictures\\pet\\dog\\usualDog";
    public:   
    Dog(std::string name);  
    Dog();   
    bool death() override;
    std::string getType() override;
};

#endif
