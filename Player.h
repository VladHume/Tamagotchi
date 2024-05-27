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
    Player(std::string name, Pet* pet, int playerSteps);
    Player();
    void increasePlayerSteps();
    int getSteps();
    void setSteps(int playerSteps);
    std::string getName();
    Pet* getPet();
};

#endif
