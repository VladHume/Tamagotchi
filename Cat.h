#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "Pet.h"
#include <string>

class Cat : public Pet{
    private:
    int lives_;
    public:   
    Cat(std::string name);    
    Cat(); 
    int getLives(); //+
    void setLives(int lives); //+
    bool death() override;
    std::string getType() override;
};

#endif
