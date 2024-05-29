#include "Menu.h"

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

int Menu::readControlKeys()
{
    int userKey = 0;
    system("stty raw");
    while (true)
    {
        userKey = getchar(); 
        if(isCorrectControlKey(userKey))
        {
            break;     
        }      
    }
    system("stty cooked");
    return userKey;
}

bool Menu::isCorrectControlKey(int key) 
{ 
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_RIGHT;
}


void Menu::displayPetInteractions(const std::vector<std::string>& opt, int maxLen)
{
    PrintUtility::cleanScreen(); 
    std::cout << PrintUtility::drawLine(maxLen);
    for (int i = 0; i < static_cast<int>(opt.size()); ++i)
    {
        int spaces = (maxLen - (PrintUtility::charCounter(opt[i])/2))-2;
        if (i == currentOption)
        {
            std::cout << "| " << setColor << opt[i] << " ■" << unsetColor << std::setw(spaces-2) << std::setfill(' ') << "|" << std::endl;
        }
        else std::cout << "| " << opt[i] << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
    }
    std::cout << PrintUtility::drawLine(maxLen);
}

// void Menu::displayMenuOprions(const std::vector<std::string>& opt)

int Menu::chooseVertOption(const std::vector<std::string>& opt, int maxLen)
{
    int numOptions = opt.size();
    while (true)
    {
        displayPetInteractions(opt, maxLen);
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

// bool Menu::chooseYesNo(const std::vector<std::string>& opt)
// {   
//     int numOptions = opt.size();
//     while (true)
//     {
//         int = readControlKeys();
//     }
    
// }

void Menu::interactWithPet(Player* player)
{
    std::string petName = player->getPet()->getName();
    int playerChoice = chooseVertOption(menuOptions, LINE_BETWEEN_OPT);
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
    Menu menu;
    Dog* myDog = new Dog("Buddy");
    Player player("John", myDog, 100);
    menu.interactWithPet(&player);


    return 0;
}
