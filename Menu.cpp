#include "Menu.h"
#include "TimeControl.h"
#include "PrintUtility.h"

Menu::Menu()
{
    player = new Player();
    fileList = FileUtility::fileList();
    numOptions = 0;   
    currentOption = 0;
    isMainScreen = true; 
    isGameRunning = true; 
}

Menu::~Menu()
{
    delete player;
}

//manipulator
//set green for selected option
std::ostream & setColor(std::ostream &stream)
{
    stream << "\x1b[1;32m";
    return stream;
}

//unset green
std::ostream & unsetColor(std::ostream &stream)
{
    stream << "\x1b[1;37m";
    return stream;
}

//a function to read input in raw mode
int Menu::readControlKeys()
{
    int userKey = 0;
    //enter raw mode
    system("stty raw");
    while (true)
    {
        userKey = getchar(); 
        if(isCorrectControlKeys(userKey))
        {
            break;     
        }      
    }
    //exit raw mode
    system("stty cooked");
    return userKey;
}


bool Menu::getIsMainScreen(){
    return isMainScreen;
}

//all keys user need to use and its validation
bool Menu::isCorrectControlKeys(int key) 
{ 
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN;
}

//a function that displays(animations) main screen where user can interact with pet 
void Menu::displayMainScreen(Player *player)
{
    PrintUtility::cleanScreen(); 
    player->getPet()->drawPet();
    PrintUtility::showPetStats(player);
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
    PrintUtility::showPetInfo(player);

    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
    for (const auto& option : petOptions)
    {
        int spaces = (SCREEN_WIDGHT - (PrintUtility::charCounter(option) / 2)) - 2;
        if (&option == &petOptions[currentOption])
        {
            //display selected option
            std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
        }
        else
        {
            //display unselected option
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
}

//a function that displays(animations) main screen where user can interact with pet 
void Menu::displayChoosePetScreen()
{
    PrintUtility::cleanScreen();
    int const MENU_TEXT_CHP = 29;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_CHP) / 2) << " " << PrintUtility::drawLine(MENU_TEXT_CHP);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_CHP) / 2) << " " << "|  Оберіть свого улюбленця!  |" << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_CHP) / 2) << " " << PrintUtility::drawLine(MENU_TEXT_CHP);

    std::cout << '\n' << PrintUtility::drawLine(SCREEN_WIDGHT);
    int index = 0;
    for (const auto& option : choosePetOptions)
    {
        int spaces = (SCREEN_WIDGHT - (PrintUtility::charCounter(option) / 2 + 1));
        if (index == currentOption)
        {  
             //display selected option
            std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
            if (index == 0)
            {
                //the first element of vactor is dog so it prints dog pic
                FileUtility::printFileContent(chooseDogPic);
                std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
            }
            else
            {   //the second is cat
                FileUtility::printFileContent(chooseCatPic);
                std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
            }
        }
        else 
        {
            //display unselected option
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
            std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
        }
        ++index;
    }
}


void Menu::displayMenuScreen()
{
    PrintUtility::cleanScreen();
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
    for (const auto& option : menuOptions)
    {
        int spaces = (SCREEN_WIDGHT - (PrintUtility::charCounter(option) / 2)) - 2;
        if (&option == &menuOptions[currentOption])
        {
             //display selected option
            std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
        }
        else
        {    
            //display unselected option
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
}

//the main function that determines what exactly the user has entered
int Menu::chooseVertOption(Player *player, displayVarients a, std::vector<std::string> &opt)
{
    int numOptions = opt.size();
    currentOption = currentOption % numOptions;
    while (true)
    {
        //extension - this is the type of display option we need to display
        if (a == FULL_SCREEN) {
            displayMainScreen(player);
        } else if (a == PART_SCREEN) {
            displayChoosePetScreen();  
        }else if(a == FILE_SCREEN){
            displayFileScreen();
        }else if(a == MAIN_SCREEN){
            displayMenuScreen();
        }
        else std::cerr <<  "Invalid extension" << std::endl;

        int key = readControlKeys();
        switch (key)
        {
            case ARROW_UP:
            //to move the current selection up 
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case ARROW_DOWN:
            //to move the current selection down
                currentOption = (currentOption + 1) % numOptions;
                break;
            case ENTER:
                return currentOption; 
            default:
                break;
        }
    }
}
//
int Menu::choosePetScreen()
{
    int playerChoice = chooseVertOption(player, PART_SCREEN, choosePetOptions);
    return playerChoice;
}

void Menu::interactWithPet(Player* player)
{
    
    std::string petName = player->getPet()->getName();
    int playerChoice = chooseVertOption( player, FULL_SCREEN, petOptions);
    // clears the buffer that catches the extra char
    std::cin.clear();
    switch (playerChoice)
    {
        // interact with pet: feed, clean, etc. and increase steps
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
        //  when pet goes to sleep he is actually sleeping
        player->getPet()->goToSleep();
        player->increasePlayerSteps();
        break;
    case 7:
        isMainScreen = false; 
        mainMenu();
        return;                       
    default:
        break;
    }
}

void Menu::mainScreen(std::string fileName)
{
    Player player;
    FileUtility *fu = FileUtility::createFile(fileName);
    //read from file to player
    fu->read(&player);
    //In the constructor of the time controller
    //the timeloop function is launched
    //which runs on a separate thread
    TimeControl tc(&player, fu, this);

    isMainScreen = true;
    while(isMainScreen)
    {
        interactWithPet(&player);
    }
}

//a function that prints tamagotchi title
void Menu::menuScreen()
{
    const int MENU_TEXT_S = 36;
    PrintUtility::cleanScreen();
    FileUtility::printFileContent(startBanner);

    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_S)/2) << " " <<  PrintUtility::drawLine(MENU_TEXT_S);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_S)/2) << " " << "|  Нажміть ENTER щоб почати гру..  |" << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_S)/2) << " " << PrintUtility::drawLine(MENU_TEXT_S);

    std::cin.get(); 
}

//a function that prints end game title
void Menu::deathScreen()
{
    const int MENU_TEXT_E = 31;
    PrintUtility::cleanScreen();
    FileUtility::printFileContent(endBanner);
    isGameRunning = false;

    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_E)/2) << " " <<  PrintUtility::drawLine(MENU_TEXT_E);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_E)/2) << " " << "|  Нажміть ENTER щоб вийти..  |" << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_E)/2) << " " << PrintUtility::drawLine(MENU_TEXT_E);

    std::cin.get(); 
}

void Menu::displayFileScreen()
{
    PrintUtility::cleanScreen();
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
    for (const auto& option : fileList)
    {
    int spaces = (SCREEN_WIDGHT - (PrintUtility::charCounter(option) / 2)) - 2;
    if (&option == &fileList[currentOption])
    {
        std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
    }
    else
        {
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
}

void Menu::deleteSave()
{
    fileList = FileUtility::fileList();
    if(fileList.empty()){
        mainMenu();
        return;
    }
    int playerChoice = chooseVertOption(player, FILE_SCREEN, fileList);
    FileUtility::deleteFile(fileList[playerChoice]);
    fileList = FileUtility::fileList();
    mainMenu();
}

//a funtion that determinates with wich file we are working
void Menu::chooseSave(){
    fileList = FileUtility::fileList();
    //if file list with saves is empty
    if(fileList.empty()){
        mainMenu();
        return;
    }
    int playerChoice = chooseVertOption(player, FILE_SCREEN, fileList);
    mainScreen(fileList[playerChoice]);
}

//a funtion that literally do menu menu
void Menu::mainMenu()
{
    std::cin.clear();
    int playerChoice = chooseVertOption(player, MAIN_SCREEN, menuOptions);
    switch(playerChoice){
        case 0:
            startNewGame();
            break;
        case 1:
            chooseSave();
            break;
        case 2:
            deleteSave();
            break;
        case 3:
            break;
        default:
            break;
    }
}

//a function that creates new file save
void Menu::startNewGame()
{
    const int MENU_TEXT_STARTGAME = 25;
    PrintUtility::cleanScreen();
    std::string playerName;
    std::string petName;

    FileUtility::printFileContent(welcomeText);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_STARTGAME)/2) << " " << "Введіть ім'я власника: ";
    std::cin >> playerName;
    playerName = PrintUtility::limitedInput(playerName, LIMIT_FOR_INPUT);
і
    PrintUtility::cleanScreen();
    FileUtility::printFileContent(welcomeText);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_STARTGAME)/2) << " " << "Введіть ім'я улюбленця: ";
    std::cin >> petName;
    petName = PrintUtility::limitedInput(petName, LIMIT_FOR_INPUT);
    PrintUtility::cleanScreen();

    player->setName(playerName);
    player->setSteps(0);

    Pet* pet;
    int petType = choosePetScreen();

    //type of pet
    if (choosePetOptions[petType] == "Собака") {
        pet = new Dog();
    } else if (choosePetOptions[petType] == "Кіт") {
        pet = new Cat();
    } else {
        return;
    }
    pet->setName(petName);
    player->setPet(pet);

    FileUtility *fileUtility;
    fileUtility = FileUtility::createFile(FileUtility::createFileName(player));

    std::time_t now = std::time(nullptr);
    std::tm currentTime = *std::localtime(&now);
    fileUtility->updateFile(player, currentTime);
    mainScreen(fileUtility->getFileName());

}
