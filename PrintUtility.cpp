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
    std::cout << "| " << strRested << drawStats(satiated) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strRested)/2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strSatiated << drawStats(rested) << std::right << std::setw(SCREEN_WIDGHT - statsLenght - charCounter(strSatiated)/2) << std::setfill(' ') << "|" << std::endl;


}
void PrintUtility::showPetInfo(Player* player) {
    const std::string strPetName = "Ім'я улюбленця: ";
    const std::string strOwnerName = "Ім'я власника: ";
    const std::string strSteps = "Кроки власника: ";
    const std::string strMood = "Настрій улюбленця: ";

    std::string ownerName = player->getName();
    std::string petName = player->getPet()->getName();
    std::string petMood = player->getPet()->getStringMood();
    int ownerSteps = player->getSteps();

    std::cout << "| " << strOwnerName << ownerName << std::right << std::setw(SCREEN_WIDGHT - charCounter(strOwnerName + ownerName) / 2 - 2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strPetName << petName << std::right << std::setw(SCREEN_WIDGHT - charCounter(strPetName + petName) / 2 - 2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strSteps << ownerSteps << std::right << std::setw(SCREEN_WIDGHT - charCounter(strSteps + std::to_string(ownerSteps))/ 2  - 2) << std::setfill(' ') << "|" << std::endl;
    std::cout << "| " << strMood << petMood << std::right << std::setw(SCREEN_WIDGHT - charCounter(strMood + petMood) / 2 - 2) << std::setfill(' ') << "|" << std::endl;
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
    std::thread t1 (&PrintUtility::interactWithPet, this, &player); 
    while(player.getPet()->getIsAlive())
    {
        
        cleanScreen();
        std::cout << "asfygusyhfnks" << std::endl;
        player.getPet()->drawPet();
        showPetStats(&player);
        std::cout << drawLine(SCREEN_WIDGHT);
        showPetInfo(&player);
        // interactWithPet(&player);
    }
    t1.join();
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
    return dots + std::string(lenght - dotcount, '-')+ dots + "\n";
}

//FROM MENU

std::ostream & setColor(std::ostream &stream)
{
    stream << "\x1b[1;32m";
    return stream;
}

std::ostream & unsetColor(std::ostream &stream)
{
    stream << "\x1b[1;37m";
    return stream;
}

int PrintUtility::readControlKeys()
{
    int userKey = 0;
    system("stty raw");
    while (true)
    {
        userKey = getchar(); 
        if(isCorrectControlKeys(userKey))
        {
            break;     
        }      
    }
    system("stty cooked");
    return userKey;
}

bool PrintUtility::isCorrectControlKeys(int key) 
{ 
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_RIGHT;
}


void PrintUtility::displayVert(const std::vector<std::string>& opt, int maxLen)
{

    std::cout << drawLine(maxLen);
    for (const auto& option : opt)
    {
        int spaces = (maxLen - (charCounter(option) / 2)) - 2;
        if (&option == &opt[currentOption])
        {
            std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
        }
        else
        {
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
        }
    }
    std::cout << drawLine(maxLen);
}

void PrintUtility::displayHoriz(const std::vector<std::string>& opt, int maxLen)
{

    std::cout << drawLine(maxLen);
    for (const auto& option : opt)
    {
        if (&option == &opt[currentOption])
        {
            std::cout << setColor << option << " ■" << unsetColor;
        }
        else
        {
            std::cout << option;
        }
        std::cout << std::setw(LINE_BETWEEN) << std::setfill(' ');
    }
    std::cout << '\n' << drawLine(maxLen);
}


int PrintUtility::chooseVertOption(const std::vector<std::string>& opt, int maxLen)
{
    
    currentOption = 0;
    int numOptions = opt.size();
    while(true)
    {
        displayVert(opt, maxLen);
        int key = readControlKeys();
        switch (key)
        {
            case ARROW_UP:
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case ARROW_DOWN:
                currentOption = (currentOption + 1) % numOptions;
                break;
            case ENTER:
                return currentOption; 
            default:
                break;
        }
    }
}

int PrintUtility::chooseYesNo(const std::vector<std::string>& opt, int maxLen)
{
    currentOption = 0; 
    while (true)
    {
        displayHoriz(opt, maxLen);
        int key = readControlKeys();
        switch (key)
        {
            case ARROW_LEFT:
                currentOption = 0;
                break;
            case ARROW_RIGHT:
                currentOption = 1;
                break;
            case ENTER:
                return currentOption;
            default:
                break;
        }
    }
}
void PrintUtility::interactWithPet(Player* player)
{
    
    std::string petName = player->getPet()->getName();
    int playerChoice = chooseVertOption(petOptions, SCREEN_WIDGHT);
    std::cin.clear();
    switch (playerChoice)
    {
    case 0: //Погодувати улюбленця
        player->getPet()->feed();
        std::cout << petName << " погодовано\n";
        break;
    case 1: //Полікувати улюбленця
        player->getPet()->treat();
        std::cout << petName << " поліковано\n";
        break;
    case 2: //Покупати улюбленця
        player->getPet()->clean();
        std::cout << petName << " покупано\n";
        break;
    case 3: //Погратися з улюбленцем
        player->getPet()->play();
        std::cout << "Ви погралися з "<< petName << '\n';
        break;
    case 4: //Погладити улюбленця
        player->getPet()->pet();
        std::cout << "Ви погладили "<< petName << '\n';    
        break;
    case 5: //Вдарити улюбленця
        player->getPet()->punch();
        std::cout << "Ви вдарили "<< petName << '\n';    
        break;
    case 6: // Покласти спати
        player->getPet()->goToSleep();
        std::cout << petName << " заснув\n";    
        break;                    
    default:
        break;
    }
}
int main()
{
    PrintUtility print;
    print.mainScreen();


    // Player player;
    // FileUtility *fu = FileUtility::createFile("test.json");
    // std::cout << 1 << std::endl;
    // fu->read(&player);
    // std::cout << 2 << std::endl;
    // TimeControl tc(&player, fu);
    // std::cout << 3 << std::endl;
    // PrintUtility print12;
    // print12.interactWithPet(&player);

    return 0;
}