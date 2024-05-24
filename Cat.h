#ifndef CAT_H
#define CAT_H

#include <iostream>
#include "Pet.h"
#include <cstring>
#include <string>

class Cat : public Pet{
    private:
    int lives_;
    public:   
    Cat(std::string petName);     
    bool death() override;
};

#endif
