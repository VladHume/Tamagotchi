#ifndef PET_H
#define PET_H

#include <iostream>
#include <string>

enum class MOOD{  //+
    HAPPY, NORMAL, SAD
};

class Pet {
protected:
    int attention_;
    int health_;
    int cleanliness_;
    int fatigue_;
    int hunger_;
    std::string name_;
    bool isAlive_;
    MOOD currentMood_;  //+

public:
    Pet(std::string petName);
    Pet();

    // Гетери
    bool getIsAlive();
    int getAttention();
    int getHealth();
    int getCleanliness();
    int getFatigue();
    int getHunger();
    std::string getName();
    MOOD getMood(); //+

    // Сетери
    void setIsAlive(bool isAlive);
    void setAttention(int attention);
    void setHealth(int health);
    void setCleanliness(int cleanliness);
    void setFatigue(int fatigue);
    void setHunger(int hunger);
    void setName(std::string name);
    void setMood(MOOD mood);  //+

    virtual bool death() = 0;
    virtual std::string getType() = 0;

    void feed();
    void treat();
    void clean();
    void play();
    void pet();
    void punch();
    void goToSleep();

    void checkMood(); //+
};



#endif 
