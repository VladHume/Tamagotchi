#ifndef TIMECONTROL_H
#define TIMECONTROL_H

#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <TimePhase.h>
#include <Player.h>
#include <FileUtility.h>

class TimeControl{
    private:
        std::thread controlThread;
        std::tm timeInGame;
        std::tm timeStartGame;
        const int timePhaseChanger = 30;
        TimePhase currentPhase;
        FileUtility *filetm;
        Player *player;
    public:
        TimeControl(Player *player, FileUtility *filetm);
        void autoSave();
        void changePhaseInGame();
        void changeStatesDueToPhase();
}
#endif