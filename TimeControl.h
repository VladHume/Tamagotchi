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
#include <iomanip>
#include <sstream>
#include "Menu.h"

class TimeControl{
    private:
        Player *player;
        FileUtility *filetm;
        TimePhase currentPhase;
        Menu *menu;
        std::thread controlThread;
        std::tm timeInGame;
        std::tm timeStartGame;
        std::tm currentTime;
        const int timePhaseChanger = 15;
        
        
        
    public:
        TimeControl(Player *player, FileUtility *filetm, Menu *menu);
        ~TimeControl();
        void timeControlLoop();
        void changePhaseInGame();
        void changeStatesDueToPhase();
        void updateTimeInGame();
        void checkElapsedTimeAndUpdate();
        void updateStateBasedOnAbsenceTime(int elapsedHours);
        std::string getCurrentPhaseString();
        std::string getTimeInGameString();
        std::string getCurrentTimeString();
        TimePhase getCurrentPhase();
};
#endif