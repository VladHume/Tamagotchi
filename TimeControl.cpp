#include "TimeControl.h"

TimeControl::TimeControl(Player *player, FileUtility *filetm, Menu *menu) 
    : player(player), filetm(filetm), currentPhase(TimePhase::MORNING), menu(menu) {
    // Initialize game time with zero values
    timeInGame = std::tm{};

    // Initialize game start time with the current time
    std::time_t now = std::time(nullptr);
    timeStartGame = *std::localtime(&now);
    currentTime = *std::localtime(&now);

    // Start the control thread
    controlThread = std::thread(&TimeControl::timeControlLoop, this);
}

// Destructor for TimeControl
TimeControl::~TimeControl() {
    // Join the control thread if it's joinable
    if (controlThread.joinable()) {
        controlThread.join();
    }
}

// Main loop for controlling game time
void TimeControl::timeControlLoop() {
    int durationOfTheCurrentPhase = 0; // Duration of the current phase in seconds

    checkElapsedTimeAndUpdate();
    updateTimeInGame();

    // Main loop for updating game time and player/pet state
    while(menu->getIsMainScreen() && player->getPet()->getIsAlive()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player->setTimeInGame(getTimeInGameString());
        player->setTimePhase(getCurrentPhaseString());
        player->getPet()->nextFrame();
        player->getPet()->checkMood();
        player->getPet()->death();
        updateTimeInGame();
        filetm->updateFile(player, currentTime);

        durationOfTheCurrentPhase++;
        if((durationOfTheCurrentPhase %= timePhaseChanger) == 0) {
            changePhaseInGame();
        }
    }
    filetm->updateFile(player, currentTime);
}

// Updates the time in the game
void TimeControl::updateTimeInGame() {
    auto now = std::chrono::system_clock::now();
    auto start = std::chrono::system_clock::from_time_t(std::mktime(&timeStartGame));
    auto elapsed = now - start;

    // Get the elapsed time in hours, minutes, and seconds
    auto hours = std::chrono::duration_cast<std::chrono::hours>(elapsed).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed).count() % 60;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() % 60;

    // Update timeInGame
    timeInGame.tm_hour = hours;
    timeInGame.tm_min = minutes;
    timeInGame.tm_sec = seconds;

    // Update currentTime with the current local time
    std::time_t currentNow = std::time(nullptr);
    currentTime = *std::localtime(&currentNow);
}

// Changes the current phase in the game
void TimeControl::changePhaseInGame() {
    // Cycle through the phases in a circular manner
    currentPhase = static_cast<TimePhase>((static_cast<int>(currentPhase) + 1) % (static_cast<int>(TimePhase::NIGHT) + 1));
    changeStatesDueToPhase();
}

// Updates the pet's state based on the current phase
void TimeControl::changeStatesDueToPhase() {
    switch (currentPhase) {
        case TimePhase::MORNING:
            player->getPet()->setAttention(player->getPet()->getAttention() - 20);
            player->getPet()->setCleanliness(player->getPet()->getCleanliness() - 10);
            player->getPet()->setHealth(player->getPet()->getHealth() - 10);
            player->getPet()->setRested(player->getPet()->getRested() - 2);
            player->getPet()->setSatiated(player->getPet()->getSatiated() - 25);
            break;
        case TimePhase::AFTERNOON:
            player->getPet()->setAttention(player->getPet()->getAttention() - 20);
            player->getPet()->setCleanliness(player->getPet()->getCleanliness() - 20);
            player->getPet()->setHealth(player->getPet()->getHealth() - 10);
            player->getPet()->setRested(player->getPet()->getRested() - 25);
            player->getPet()->setSatiated(player->getPet()->getSatiated() - 20);
            break;
        case TimePhase::EVENING:
            player->getPet()->setAttention(player->getPet()->getAttention() - 20);
            player->getPet()->setCleanliness(player->getPet()->getCleanliness() - 20);
            player->getPet()->setHealth(player->getPet()->getHealth() - 30);
            player->getPet()->setRested(player->getPet()->getRested() - 20);
            player->getPet()->setSatiated(player->getPet()->getSatiated() - 10);
            break;
        case TimePhase::NIGHT:
            player->getPet()->setAttention(player->getPet()->getAttention() - 20);
            player->getPet()->setCleanliness(player->getPet()->getCleanliness() - 20);
            player->getPet()->setHealth(player->getPet()->getHealth() - 20);
            player->getPet()->setRested(player->getPet()->getRested() - 20);
            player->getPet()->setSatiated(player->getPet()->getSatiated() - 20);
            break;
        default:
            break;
    }
}

// Checks the elapsed time since the last saved time and updates the pet's state
void TimeControl::checkElapsedTimeAndUpdate() {
    std::tm savedTime = filetm->readTimeEndGame();
    
    // Convert times to time_t for calculating the difference
    std::time_t savedTime_t = std::mktime(const_cast<std::tm*>(&savedTime));
    std::time_t nowTime_t = std::mktime(&timeStartGame);

    // Calculate the difference in seconds
    double elapsedSeconds = std::difftime(nowTime_t, savedTime_t);

    // Calculate the difference in hours
    int elapsedHours = static_cast<int>(elapsedSeconds / 3600);

    // Update the pet's state based on the elapsed time
    updateStateBasedOnAbsenceTime(elapsedHours);
}

// Updates the pet's state based on the time the player was absent
void TimeControl::updateStateBasedOnAbsenceTime(int elapsedHours) {
    player->getPet()->setAttention(player->getPet()->getAttention() - (3 * elapsedHours));
    player->getPet()->setCleanliness(player->getPet()->getCleanliness() - (3 * elapsedHours));
    player->getPet()->setHealth(player->getPet()->getHealth() - (3 * elapsedHours));
    player->getPet()->setRested(player->getPet()->getRested() - (3 * elapsedHours));
    player->getPet()->setSatiated(player->getPet()->getSatiated() - (3 * elapsedHours));
}

// Gets the current phase of the game
TimePhase TimeControl::getCurrentPhase() {
    return currentPhase;
}

// Returns the current phase of the game as a string
std::string TimeControl::getCurrentPhaseString() {
    switch (currentPhase) {
        case TimePhase::MORNING:
            return "РАНОК";
        case TimePhase::AFTERNOON:
            return "ДЕНЬ ";
        case TimePhase::EVENING:
            return "ВЕЧІР";
        case TimePhase::NIGHT:
            return "НІЧ  ";
        default:
            return " ";
    }
}

// Returns the elapsed time in the game as a string
std::string TimeControl::getTimeInGameString() {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << timeInGame.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << timeInGame.tm_min << ":"
        << std::setw(2) << std::setfill('0') << timeInGame.tm_sec;
    return oss.str();
}

// Returns the current local time as a string
std::string TimeControl::getCurrentTimeString() {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << currentTime.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << currentTime.tm_min << ":"
        << std::setw(2) << std::setfill('0') << currentTime.tm_sec;
    return oss.str();
}
