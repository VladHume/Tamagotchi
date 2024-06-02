#ifndef PET_H
#define PET_H

#include <iostream>
#include <string>
#include "Frames.h"

const int MAX_VALUE = 100;
const int MIN_VALUE = 0;

enum class MOOD{  
    HAPPY, NORMAL, SAD
};

class Pet {
protected:
    int attention_;
    int health_;
    int cleanliness_;
    int rested_;
    int satiated_;
    std::string name_;
    bool isAlive_;
    MOOD currentMood_;
    bool isAwaken_;

    Frames *happy_;
    Frames *sad_;
    Frames *usual_;
    Frames *sleep_;
    Frames *death_;

public:
    Pet(std::string name, Frame *happy, Frame *sad, Frame *usual, Frame *sleep, Frame *death);
    Pet();

    // Гетери
    bool getIsAlive();
    int getAttention();
    int getHealth();
    int getCleanliness();
    int getRested();
    int getSatiated();
    std::string getName();
    MOOD getMood(); 
    std::string getStringMood();
    bool getIsAwaken();

    // Сетери
    void setIsAlive(bool isAlive);
    void setAttention(int attention);
    void setHealth(int health);
    void setCleanliness(int cleanliness);
    void setRested(int rested);
    void setSatiated(int satiated);
    void setName(std::string name);
    void setMood(MOOD mood);  
    void setIsAwaken(bool isAwaken);

    virtual bool death() = 0;
    void nextFrame();
    void drawPet();
    void wakeUp();

    virtual std::string getType() = 0;

    void feed();
    void treat();
    void clean();
    void play();
    void pet();
    void punch();
    void goToSleep();

    void checkBounds();
    void checkMood(); 
};



#endif 
