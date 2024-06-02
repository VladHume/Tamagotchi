#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "Pet.h"
#include <string>

class Player{
private:
    std::string name_;
    Pet* pet_;
    int playerSteps_;
public:
    Player(std::string name, Pet* pet, int playerSteps);
    Player();
    ~Player();
    void increasePlayerSteps();
    int getSteps();
    void setSteps(int playerSteps);
    std::string getName();
    void setName(std::string name);
    Pet* getPet();
    void setPet(Pet* pet); 

};

#endif
