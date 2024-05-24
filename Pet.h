#ifndef PET_H
#define PET_H
#include <iostream>
#include <cstring>
#include <string>

class Pet{
    private:
    int attention_;
    int health_;
    int cleanliness_;
    int fatigue_;
    int hunger_;
    std::string name_;
    bool isAlive_;
    public:

    Pet(std::string petName);

    bool getIsAlive();
    void setIsAlive(bool isAlive);
    
    void setAttention(int attention);
    void setHealth(int health);
    void setCleanliness(int cleanliness);
    void setFatigue(int fatigue);
    void setHunger(int hunger);


    virtual bool death() = 0;
    void feed();
    void treat();
    void clean();
    void play();
    void pet();
    void punch();
    void goToSleep();
};

#endif 
