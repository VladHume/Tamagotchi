#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Pet.h"
#include <cstring>
#include <string>

class Player{
    private:
    int playerSteps_;
    std::string name_;
    Pet* pet_;
    public:
    Player(std::string name, Pet* pet);
    int countPlayerSteps();
    int getSteps();
    void setSteps();
}

#endif
