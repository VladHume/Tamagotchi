#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "Pet.h"
#include "Frames.h"
#include <string>

class Cat : public Pet{
    private:
    //picture directories
    const std::string happyPath = "pictures\\pet\\cat\\happyCat";
    const std::string sadPath = "pictures\\pet\\cat\\sadCat";
    const std::string sleepPath = "pictures\\pet\\cat\\sleepCat";
    const std::string deathPath = "pictures\\pet\\cat\\deathCat";
    const std::string usualPath = "pictures\\pet\\cat\\usualCat";
    public:   
    Cat(std::string name);    
    Cat(); 
    std::string getType() override;
};

#endif
