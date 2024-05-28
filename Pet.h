#ifndef PET_H
#define PET_H
#include <iostream>
#include <cstring>
#include <string>

class Pet{
    protected:
    int attention_;
    int health_;
    int cleanliness_;
    int fatigue_;
    int hunger_;
    std::string name_;
    bool isAlive_;
    public:

    Pet(std::string petName);

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
