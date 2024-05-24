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
    int getAttention();
    int getHealth();
    int getCleanliness();
    int getFatigue();
    int getHunger();

    void setAttention(int attention);
    void setHealth(int health);
    void setCleanliness(int cleanliness);
    void setFatigue(int fatigue);
    void setHunger(int hunger);
    void setName(std::string name);
    void setIsAlive(bool isAlive);

    virtual bool death() = 0;
    virtual void feed() = 0;
    virtual void treat() = 0;
    virtual void clean() = 0;
    virtual void play() = 0;
    virtual void pet() = 0;
    virtual void punch() = 0;
    virtual void goToSleep() = 0; 
};

#endif 
