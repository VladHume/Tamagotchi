#include "Menu.h"

Menu::Menu()
{
    player = new Player();
}

Menu::~Menu()
{
    delete player;
}

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
        if(isCorrectControlKeys(userKey))
        {
            break;     
        }      
    }
    system("stty cooked");
    return userKey;
}

bool Menu::isCorrectControlKeys(int key) 
{ 
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_RIGHT;
}


void Menu::displayVert(const std::vector<std::string>& opt, int maxLen, Player *player)
{
    PrintUtility::cleanScreen(); 
    player->getPet()->drawPet();
    PrintUtility::showPetStats(player);
    std::cout << PrintUtility::drawLine(maxLen);
    PrintUtility::showPetInfo(player);
    std::cout << PrintUtility::drawLine(maxLen);
    for (const auto& option : opt)
    {
        int spaces = (maxLen - (PrintUtility::charCounter(option) / 2)) - 2;
        if (&option == &opt[currentOption])
        {
            std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
        }
        else
        {
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(maxLen);
}

int Menu::chooseVertOption(const std::vector<std::string>& opt, int maxLen, Player *player)
{
    
    currentOption = 0;
    int numOptions = opt.size();
    while (true)
    {
        displayVert(opt, maxLen, player);
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


void Menu::interactWithPet(Player* player)
{
    
    std::string petName = player->getPet()->getName();
    int playerChoice = chooseVertOption(petOptions, SCREEN_WIDGHT, player);
    std::cin.clear();
    switch (playerChoice)
    {
    case 0: 
        player->getPet()->feed();
        player->increasePlayerSteps();
        break;
    case 1:
        player->getPet()->treat();
        player->increasePlayerSteps();
        break;
    case 2:
        player->getPet()->clean();
        player->increasePlayerSteps();
        break;
    case 3: 
        player->getPet()->play();
        player->increasePlayerSteps();
        break;
    case 4:
        player->getPet()->pet();
        player->increasePlayerSteps();
        break;
    case 5: 
        player->getPet()->punch(); 
        player->increasePlayerSteps();
        break;
    case 6: 
        player->getPet()->goToSleep();
        player->increasePlayerSteps();
        break;
    case 7:
        isMainScreen = false; 
        break;                       
    default:
        break;
    }
}

void Menu::mainScreen()
{
    Player player;
    FileUtility *fu = FileUtility::createFile("test.json");
    std::cout << 1 << std::endl;
    fu->read(&player);
    std::cout << 2 << std::endl;
    TimeControl tc(&player, fu);
    std::cout << 3 << std::endl;
    while(isMainScreen && player.getPet()->getIsAlive())
    {
        interactWithPet(&player);
    }
}

int main()
{
    Menu print;
    print.mainScreen();

    return 0;
}