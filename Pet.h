#ifndef PET_H
#define PET_H

#include <iostream>
#include <string>
#include "Frames.h"

const int MAX_VALUE = 100; //the maximum value of the level of needs
const int MIN_VALUE = 0;  //the minimum value of the level of needs


//enum for mood of pet
enum class MOOD{  
    HAPPY, NORMAL, SAD
};

class Pet {
protected:
    std::string name_;
    int attention_;
    int health_;
    int cleanliness_;
    int rested_;
    int satiated_;

    bool isAlive_;
    MOOD currentMood_;
    bool isAwaken_;
    Frames *happy_;
    Frames *sad_;
    Frames *usual_;
    Frames *sleep_;
    Frames *death_;

public:
    Pet(std::string name, Frames *happy, Frames *sad, Frames *usual, Frames *sleep, Frames *death);
    Pet();
    virtual ~Pet();
    // getters
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

    // setters
    void setIsAlive(bool isAlive);
    void setAttention(int attention);
    void setHealth(int health);
    void setCleanliness(int cleanliness);
    void setRested(int rested);
    void setSatiated(int satiated);
    void setName(std::string name);
    void setMood(MOOD mood);  
    void setIsAwaken(bool isAwaken);

    bool death() ; //method for death 
    void nextFrame();  //method for rearranging the frame when drawing a pet
    void drawPet();  ///a method for drawing a pet depending on its mood
    void wakeUp();  //method for wake up the pet

    virtual std::string getType() = 0;  //method for determining the type of animal

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
