#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include "TimePhase.h"
#include "Player.h"
#include "Pet.h"
#include "Dog.h"
#include "Cat.h"
#include "FileUtility.h"

class TimeControl{
    private:
        std::thread controlThread;
        std::tm timeInGame;
        std::tm timeStartGame;
        const int timePhaseChanger = 3;
        TimePhase currentPhase;
        FileUtility *filetm;
        Player *player;
    public:
        TimeControl(Player *player, FileUtility *filetm);
        ~TimeControl();
        void timeControlLoop();
        void changePhaseInGame();
        void changeStatesDueToPhase();
        void updateTimeInGame();
};
#endif