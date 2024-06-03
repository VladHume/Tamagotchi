#include "PrintUtility.h"

void PrintUtility::cleanScreen()
{
    system("clear");
}

int PrintUtility::charCounter(const std::string text)
{
    int count = 0;
    for (char c : text)
    {
        if (c == ' ' || c == ':' || c == '\'' || (c >= 48 && c <=57))
            count++;
    }
    return count + text.length();
}

void PrintUtility::showPetStats(Player *player)
{
    const std::string strAttention = "Увага: ";
    const std::string strHealth = "Здоров'я: ";
    const std::string strCleanliness = "Чистота: ";
    const std::string strSatiated = "Ситість: ";
    const std::string strRested = "Відпочинок: ";
    const int statsLenght = 12; 
    int attention = player->getPet()->getAttention();
    int health = player->getPet()->getHealth();
    int cleanliness = player->getPet()->getCleanliness();
    int rested = player->getPet()->getRested();
    int satiated = player->getPet()->getSatiated();

    std::cout << "| " << strAttention << drawStats(attention) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strAttention)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strHealth << drawStats(health) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strHealth)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strCleanliness << drawStats(cleanliness) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strCleanliness)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strRested << drawStats(rested) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strRested)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strSatiated << drawStats(satiated) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strSatiated)/2) << std::setfill(' ') << "|" << std::endl;


}
void PrintUtility::showPetInfo(Player* player) {
    const std::string strPetName = "Ім'я улюбленця: ";
    const std::string strOwnerName = "Ім'я власника: ";
    const std::string strSteps = "Кроки власника: ";
    const std::string strMood = "Настрій улюбленця: ";
    const std::string strLives = "Кількість життів: ";

    std::string ownerName = player->getName();
    std::string petName = player->getPet()->getName();
    std::string petMood = player->getPet()->getStringMood();
    int ownerSteps = player->getSteps();

    std::cout << "| " << strOwnerName << ownerName << std::right << std::setw(SCREEN_WIDGHT - charCounter(strOwnerName + ownerName) / 2 - 2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strPetName << petName << std::right << std::setw(SCREEN_WIDGHT - charCounter(strPetName + petName) / 2 - 2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strSteps << ownerSteps << std::right << std::setw(SCREEN_WIDGHT - charCounter(strSteps + std::to_string(ownerSteps))/ 2  - 2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strMood << petMood << std::right << std::setw(SCREEN_WIDGHT - charCounter(strMood + petMood) / 2 - 2) << std::setfill(' ') << "|" << std::endl;
}

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

std::string PrintUtility::drawLine(int lenght)
{
    std::string dots = "..";
    const int dotcount = 4;
    return dots + std::string(lenght - dotcount, '-')+dots + "\n";
}
