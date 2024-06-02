#include "TimeControl.h"
//#include "PrintUtility.h"

TimeControl::TimeControl(Player *player, FileUtility *filetm) : player(player), filetm(filetm), currentPhase(TimePhase::MORNING) {
    // Ініціалізація часу гри нульовими значеннями 
    timeInGame = std::tm{};

    // Ініціалізація часу початку гри поточним часом
    std::time_t now = std::time(nullptr);
    timeStartGame = *std::localtime(&now);
    currentTime = *std::localtime(&now);
        
    controlThread = std::thread(&TimeControl::timeControlLoop, this);
}

TimeControl::~TimeControl() {
    if (controlThread.joinable()) {
        controlThread.join();
    }
}

void TimeControl::timeControlLoop(){
    int durationOfTheCurrentPhase = 0; //к-сть часу, який триває поточна фаза
    checkElapsedTimeAndUpdate();
    updateTimeInGame();
    while(player->getPet()->getIsAlive()){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player->getPet()->nextFrame();
        player->getPet()->checkMood();
        updateTimeInGame();
        filetm->updateFile(player, currentTime);
        durationOfTheCurrentPhase++;
        if((durationOfTheCurrentPhase %= timePhaseChanger) == 0){
            changePhaseInGame();
            player->getPet()->death();
        }
    }
    filetm->updateFile(player, currentTime);
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

    std::time_t currentNow = std::time(nullptr);
    currentTime = *std::localtime(&currentNow);
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

void TimeControl::checkElapsedTimeAndUpdate() {
    std::tm savedTime = filetm->readTimeEndGame();
    
    // Конвертуємо часи в time_t для обчислення різниці
    std::time_t savedTime_t = std::mktime(const_cast<std::tm*>(&savedTime));
    std::time_t nowTime_t = std::mktime(&timeStartGame);

    // Обчислення різниці в секундах
    double elapsedSeconds = std::difftime(nowTime_t, savedTime_t);

    // Обчислення різниці в годинах
    int elapsedHours = static_cast<int>(elapsedSeconds / 3600);

    updateStateBasedOnAbsenceTime(elapsedHours);
}

void TimeControl::updateStateBasedOnAbsenceTime(int elapsedHours){
    player->getPet()->setAttention(player->getPet()->getAttention() - (3*elapsedHours));
    player->getPet()->setCleanliness(player->getPet()->getCleanliness() - (3*elapsedHours));
    player->getPet()->setHealth(player->getPet()->getHealth() - (3*elapsedHours));
    player->getPet()->setRested(player->getPet()->getRested() - (3*elapsedHours));
    player->getPet()->setSatiated(player->getPet()->getSatiated() - (3*elapsedHours));
}

TimePhase TimeControl::getCurrentPhase() {
    return currentPhase;
}

std::string TimeControl::getCurrentPhaseString() {
    switch (currentPhase) {
        case TimePhase::MORNING:
            return "РАНОК";
        case TimePhase::AFTERNOON:
            return "ДЕНЬ";
        case TimePhase::EVENING:
            return "ВЕЧІР";
        case TimePhase::NIGHT:
            return "НІЧ";
        default:
            return " ";
    }
}

std::string TimeControl::getTimeInGameString() {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << timeInGame.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << timeInGame.tm_min << ":"
        << std::setw(2) << std::setfill('0') << timeInGame.tm_sec;
    return oss.str();
}

std::string TimeControl::getCurrentTimeString() {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << currentTime.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << currentTime.tm_min << ":"
        << std::setw(2) << std::setfill('0') << currentTime.tm_sec;
    return oss.str();
}

// int main(){
//     Player player;
//     FileUtility *fu = FileUtility::createFile("test.json");
//     fu->read(&player);
//     TimeControl tc(&player, fu);
//     while(true){
//         PrintUtility::cleanScreen();
//         std::cout << tc.getTimeInGameString() << std::endl;
//     }
    
//     // while(player.getPet()->getIsAlive()){
//     //     PrintUtility::cleanScreen();
//     //     player.getPet()->drawPet();
//     // }

//     return 0;
// }