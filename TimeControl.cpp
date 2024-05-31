#include "TimeControl.h"

TimeControl::TimeControl(Player *player, FileUtility *filetm) : player(player), filetm(filetm), currentPhase(TimePhase::MORNING) {
    // Ініціалізація часу гри нульовими значеннями
    timeInGame = std::tm{};

    // Ініціалізація часу початку гри поточним часом
    std::time_t now = std::time(nullptr);
    timeStartGame = *std::localtime(&now);
        
    controlThread = std::thread(&TimeControl::timeControlLoop, this);
}

TimeControl::~TimeControl() {
    if (controlThread.joinable()) {
        controlThread.join();
    }
}

void TimeControl::timeControlLoop(){
    int durationOfTheCurrentPhase = 0;
    while(player->getPet()->getIsAlive()){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        filetm->updateFile(player);
        durationOfTheCurrentPhase++;
        if(durationOfTheCurrentPhase % timePhaseChanger == 0){
            changePhaseInGame();
            updateTimeInGame();
            player->getPet()->death();
        }
    }
    filetm->updateFile(player);
}

void TimeControl::updateTimeInGame() {
    auto now = std::chrono::system_clock::now();
    auto start = std::chrono::system_clock::from_time_t(std::mktime(&timeStartGame));
    auto elapsed = now - start;

    // Отримання тривалості в годинах, хвилинах та секундах
    auto hours = std::chrono::duration_cast<std::chrono::hours>(elapsed).count();
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed).count() % 60;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() % 60;

    // Оновлення timeInGame
    timeInGame.tm_hour = hours;
    timeInGame.tm_min = minutes;
    timeInGame.tm_sec = seconds;
}

void TimeControl::changePhaseInGame(){
    currentPhase = static_cast<TimePhase>((static_cast<int>(currentPhase) + 1) % (static_cast<int>(TimePhase::NIGHT) +1));
    changeStatesDueToPhase();
}

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

TimePhase TimeControl::getCurrentPhase() {
    return currentPhase;
}

std::string TimeControl::getCurrentPhaseString() {
    switch (currentPhase) {
        case TimePhase::MORNING:
            return "MORNING";
        case TimePhase::AFTERNOON:
            return "AFTERNOON";
        case TimePhase::EVENING:
            return "EVENING";
        case TimePhase::NIGHT:
            return "NIGHT";
        default:
            return " ";
    }
}
