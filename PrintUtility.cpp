#include "PrintUtility.h"
//a funtion to clear screen in the console
void PrintUtility::cleanScreen()
{
    system("clear");
}

// a function to count char and format tables
int PrintUtility::charCounter(const std::string text)
{
    int count = 0;
    for (char c : text)
    {
        //all symbols that are not cyrillic are double and in the other functions
        if (c == ' ' || (c >= 33 && c <=126))
            count++;
        count++;    
    }
    //they are devided by 2 so table could be displayed correctly
    return count/2;
}

// a function to display pet's stats
void PrintUtility::showPetStats(Player *player)
{
    //const string to display them and then count char to format tables
    const std::string strAttention = " Увага: ";
    const std::string strHealth = " Здоров'я: ";
    const std::string strCleanliness = " Чистота: ";
    const std::string strSatiated = " Ситість: ";
    const std::string strRested = " Відпочинок: ";

    //actual lenght of stats + left table bar (10 dots that represent stat scale.)
    //each dot means 10 points
    const int statsLenght = 12; 

    //get actual stats  to int variables
    int attention = player->getPet()->getAttention();
    int health = player->getPet()->getHealth();
    int cleanliness = player->getPet()->getCleanliness();
    int rested = player->getPet()->getRested();
    int satiated = player->getPet()->getSatiated();

    //display table and stats
    std::cout << strBar << strAttention << drawStats(attention) << std::right << std::setw(SCREEN_WIDTH - statsLenght - charCounter(strAttention) + 1) << std::setfill(' ') << strBar << std::endl;
    std::cout << strBar << strHealth << drawStats(health) << std::right << std::setw(SCREEN_WIDTH - statsLenght - charCounter(strHealth) + 1) << std::setfill(' ') << strBar << std::endl;
    std::cout << strBar << strCleanliness << drawStats(cleanliness) << std::right << std::setw(SCREEN_WIDTH - statsLenght - charCounter(strCleanliness ) + 1) << std::setfill(' ') << strBar << std::endl;
    std::cout << strBar << strRested << drawStats(rested) << std::right << std::setw(SCREEN_WIDTH - statsLenght - charCounter(strRested) + 1) << std::setfill(' ') << strBar << std::endl;
    std::cout << strBar << strSatiated << drawStats(satiated) << std::right << std::setw(SCREEN_WIDTH - statsLenght - charCounter(strSatiated) + 1) << std::setfill(' ') << strBar << std::endl;
}

//similar function only for displaying information for the animal
void PrintUtility::showPetInfo(Player* player) 
{
    //const string to display them and then count char to format tables
    const std::string strPetName = " Ім'я улюбленця: ";
    const std::string strOwnerName = " Ім'я власника: ";
    const std::string strSteps = " Кроки власника: ";
    const std::string strMood = " Настрій улюбленця: ";
    const std::string strLives = " Кількість життів: ";


    //get actual stats to mostly string variables
    std::string ownerName = player->getName();
    std::string petName = player->getPet()->getName();
    std::string petMood = player->getPet()->getStringMood();
    int ownerSteps = player->getSteps();
    std::string timePhase = player->getTimePhase();
    std::string timeInGame = player->getTimeInGame();
    
    //display table and pet info like player's name or pet name etc
    std::cout << strBar << strOwnerName << ownerName << std::right << std::setw(MAX_LEFT_INFO - charCounter(strOwnerName + ownerName) + BETWEEN_LINES) << ' ' << timePhase;
    std::cout << std::setw(SCREEN_WIDTH  - MAX_LEFT_INFO - BETWEEN_LINES - charCounter(timePhase) - 1) << std::setfill(' ') << strBar << std::endl;
    std::cout << strBar << strPetName << petName << std::right << std::setw(MAX_LEFT_INFO - charCounter(strPetName + petName) + BETWEEN_LINES) << ' ' << timeInGame;
    std::cout << std::setw(SCREEN_WIDTH  - MAX_LEFT_INFO - BETWEEN_LINES - charCounter(timeInGame) - 1) << std::setfill(' ') << strBar << std::endl;

    std::cout << strBar << strSteps << ownerSteps << std::right << std::setw(SCREEN_WIDTH - charCounter(strSteps + std::to_string(ownerSteps))  - 1) << std::setfill(' ') << strBar << std::endl;
    std::cout << strBar << strMood << petMood << std::right << std::setw(SCREEN_WIDTH - charCounter(strMood + petMood) - 1) << std::setfill(' ') << strBar << std::endl;
}

// a funtion to get the scale of each stat;
std::string PrintUtility::drawStats(int variable)
{
    const int maxStat = 100;
    std::string statPoints = "";
    std::string statFull = "■";
    std::string statEmpty = "□";
    for (int i = 0; i < maxStat; i += 10 )
    {
        if(i < variable) statPoints += statFull;
        else statPoints += statEmpty;
    }   
    return statPoints; 
}

//a function to get line
std::string PrintUtility::drawLine(int lenght)
{
    std::string dots = "..";
    const int dotcount = 4;
    return dots + std::string(lenght - dotcount, '-')+dots + "\n";
    
}

//a function to limit user input to 25 chars(due to global const in PrintUtility header)
std::string PrintUtility::limitedInput(const std::string& input, size_t maxLength) 
{
    if (input.length() > maxLength) 
    {
        return input.substr(0, maxLength);
    }
    return input;
}
