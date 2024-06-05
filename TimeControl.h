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

class TimeControl {
private:
    Player *player;               // Pointer to the player object
    FileUtility *filetm;          // Pointer to the FileUtility object for file operations
    TimePhase currentPhase;       // Current phase of the game (e.g., Morning, Afternoon, etc.)
    Menu *menu;                   // Pointer to the Menu object
    std::thread controlThread;    // Thread for controlling the game's time loop
    std::tm timeInGame;           // Time spent in the game
    std::tm timeStartGame;        // Time when the game started
    std::tm currentTime;          // Current time
    const int timePhaseChanger = 15; // Duration of each phase in seconds

public:
    // Constructor to initialize the TimeControl with player, file utility, and menu objects
    TimeControl(Player *player, FileUtility *filetm, Menu *menu);
    
    // Destructor to ensure the control thread is properly joined
    ~TimeControl();
    
    // Main loop to control the game's time progression and phase changes
    void timeControlLoop();
    
    // Changes the current phase of the game 
    void changePhaseInGame();
    
    // Adjusts player and pet states based on the current phase of the game
    void changeStatesDueToPhase();
    
    // Updates the in-game time based on the real-world elapsed time
    void updateTimeInGame();
    
    // Checks the elapsed time since the last session and updates the game state accordingly
    void checkElapsedTimeAndUpdate();
    
    // Updates the pet's state based on the time elapsed while the game was not running
    void updateStateBasedOnAbsenceTime(int elapsedHours);
    
    // Returns the current phase of the game as a string
    std::string getCurrentPhaseString();
    
    // Returns the in-game time as a formatted string (HH:MM:SS)
    std::string getTimeInGameString();
    
    // Returns the current real-world time as a formatted string (HH:MM:SS)
    std::string getCurrentTimeString();
    
    // Returns the current phase of the game as a TimePhase enum value
    TimePhase getCurrentPhase();
};

#endif