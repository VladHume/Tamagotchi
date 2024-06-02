#include "PrintUtility.h"
const std::string PrintUtility::sbannerFile = "pictures\\banners\\start.txt";
const std::string PrintUtility::ebannerFile = "pictures\\pet\\cat\\usualCat\\Cat1.txt";
class Menu;
void PrintUtility::cleanScreen()
{
    system("clear");
}

int PrintUtility::charCounter(std::string text)
{
    int count = 0;
    for (int i = 0; text[i]; i++)
    {
        if (text[i] == ' ' || text[i] == ':' || text[i] == '\'') count++;
        count++;  
    } 
    return count;
}

void PrintUtility::showPetStats(Player *player)
{
    const std::string strAttention = "Увага: ";
    const std::string strHealth = "Здоров'я: ";
    const std::string strCleanliness = "Чистота: ";
    const std::string strSatiated = "Ситість: ";
    const std::string strRested = "Відпочинок: ";
    const int statsLenght = 12; 
    TimeControl *time_;
    int attention = player->getPet()->getAttention();
    int health = player->getPet()->getHealth();
    int cleanliness = player->getPet()->getCleanliness();
    int rested = player->getPet()->getRested();
    int satiated = player->getPet()->getSatiated();

    std::cout << "| " << strAttention << drawStats(attention) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strAttention)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strHealth << drawStats(health) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strHealth)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strCleanliness << drawStats(cleanliness) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strCleanliness)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strRested << drawStats(satiated) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strRested)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strSatiated << drawStats(rested) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strSatiated)/2) << std::setfill(' ') << "|" << std::endl;


}
void PrintUtility::showPetInfo(Player *player)
{
    const std::string strPetName = "Ім'я улюбленця: ";
    const std::string strOwnerName = "Ім'я власника: ";
    const std::string strSteps = "Кроки власника: ";
    const std::string strMood = "Настрій улюбленця: ";
      
    TimeControl *tmc;
    std::string ownerName = player->getName();
    std::string petName = player->getPet()->getName();
    // std::string petMood = player->getPet()->getMood();
    int playerSteps = player->getSteps();
    std::string timeInGame =  tmc->getTimeInGameString();
    std::string timePhase = tmc->getCurrentPhaseString();
    std::cout << "| " << strOwnerName << ownerName << std::right << std::setw(SCREEN_WIDGHT - charCounter(strOwnerName + ownerName + timePhase)/2)<< std::setfill(' ') << "|" << std::endl;
    // std::cout << "| " <<
    // std::cout << "| " <<

}

void PrintUtility::mainScreen()
{
    Player player;
    FileUtility *fu = FileUtility::createFile("test.json");
    std::cout << 1 << std::endl;
    fu->read(&player);
    std::cout << 2 << std::endl;
    TimeControl tc(&player, fu);
    std::cout << 3 << std::endl;
    while(player.getPet()->getIsAlive())
    {
        cleanScreen();
        player.getPet()->drawPet();
        showPetStats(&player);
        std::cout << drawLine(SCREEN_WIDGHT);
        showPetInfo(&player);
    }
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
    return std::string(lenght, '-') + "\n";
}

int main()
{
    PrintUtility print;
    print.mainScreen();
    return 0;
}