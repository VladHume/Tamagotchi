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
    int rested_;
    int satiated_;
    std::string petName_;
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
    int getRested();
    int getSatiated();
    std::string getPetName();
    MOOD getMood(); //+

    // Сетери
    void setIsAlive(bool isAlive);
    void setAttention(int attention);
    void setHealth(int health);
    void setCleanliness(int cleanliness);
    void setRested(int rested);
    void setSatiated(int satiated);
    void setPetName(std::string petName);
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
