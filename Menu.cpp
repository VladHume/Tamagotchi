#include "Menu.h"
#include "TimeControl.h"
#include "PrintUtility.h"

Menu::Menu()
{
    player = new Player();
    fileList = FileUtility::fileList();
    numOptions = 0;   
    isMainScreen = true; 
    isGameRunning = true; 
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

bool Menu::getIsMainScreen(){
    return isMainScreen;
}

bool Menu::isCorrectControlKeys(int key) 
{ 
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN;
}


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
            std::cout << "| " << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << std::setfill(' ') << "|" << std::endl;
        }
        else
        {
            std::cout << "| " << option << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
}

void Menu::displayChoosePetScreen()
{
    PrintUtility::cleanScreen();
    FileUtility *file = new FileUtility("test1");
    int const MENU_TEXT_CHP = 29;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_CHP) / 2) << " " << PrintUtility::drawLine(MENU_TEXT_CHP);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_CHP) / 2) << " " << "|  Оберіть свого улюбленця!  |" << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_CHP) / 2) << " " << PrintUtility::drawLine(MENU_TEXT_CHP);

    for (size_t i = 0; i < choosePetOptions.size(); ++i)
    {
        int spaces = (SCREEN_WIDGHT - (PrintUtility::charCounter(choosePetOptions[i]) / 2));
        if (static_cast<int>(i) == currentOption)
        {
            std::cout << std::right << std::setw((SCREEN_WIDGHT - spaces - 2) / 2) << " "  << setColor << choosePetOptions[i] << " ■" << unsetColor << std::endl;
            if (i == 0)
                file->printFileContent(chooseDogPic);
            else
                file->printFileContent(chooseCatPic);
        }
        else
        {
            std::cout << std::right << std::setw((SCREEN_WIDGHT - spaces) / 2)  << choosePetOptions[i] << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(SCREEN_WIDGHT);
    delete file;
}

void Menu::displayMenuScreen(){
    PrintUtility::cleanScreen();
    for (const auto& option : menuOptions)
    {
    int spaces = (SCREEN_WIDGHT - (PrintUtility::charCounter(option) / 2)) - 2;
    if (&option == &menuOptions[currentOption])
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

int Menu::chooseVertOption(Player *player, displayVarients a, std::vector<std::string>& opt)
{
    int numOptions = opt.size();
    while (true)
    {
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
//це буде реалізувати через світч в мейні
int Menu::choosePetScreen()
{
    int playerChoice = chooseVertOption(player, PART_SCREEN, choosePetOptions);
    return playerChoice;
}

void Menu::interactWithPet(Player* player)
{
    
    std::string petName = player->getPet()->getName();
    int playerChoice = chooseVertOption( player, FULL_SCREEN, petOptions);
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
    fu->read(&player);

    TimeControl tc(&player, fu, this);

    isMainScreen = true;
    while(isMainScreen /*&& player.getPet()->getIsAlive()*/)
    {
        interactWithPet(&player);
    }
}

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

void Menu::deathScreen()
{
    const int MENU_TEXT_E = 31;
    PrintUtility::cleanScreen();
    FileUtility *file = new FileUtility("test1");
    file->printFileContent(endBanner);
    delete file;    
    isGameRunning = false;

    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_E)/2) << " " <<  PrintUtility::drawLine(MENU_TEXT_E);
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_E)/2) << " " << "|  Нажміть ENTER щоб вийти..  |" << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDGHT - MENU_TEXT_E)/2) << " " << PrintUtility::drawLine(MENU_TEXT_E);

    std::cin.get(); 
}

void Menu::chooseSave(){
    fileList = FileUtility::fileList();
    if(fileList.empty()){
        mainMenu();
    }
    int playerChoice = chooseVertOption(player, FILE_SCREEN, fileList);
    mainScreen(fileList[playerChoice]);
}

void Menu::displayFileScreen(){
    PrintUtility::cleanScreen();
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

void Menu::deleteSave(){
    fileList = FileUtility::fileList();
    if(fileList.empty()){
        mainMenu();
    }
    int playerChoice = chooseVertOption(player, FILE_SCREEN, fileList);
    FileUtility::deleteFile(fileList[playerChoice]);
    fileList = FileUtility::fileList();
    mainMenu();
}

void Menu::mainMenu(){
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

void Menu::startNewGame(){
    PrintUtility::cleanScreen();
    std::string playerName;
    std::string petName;
    std::cout << "Ведіть ім'я власника: ";
    std::cin >> playerName;
    PrintUtility::cleanScreen();

    std::cout << "Ведіть ім'я улюбленця: ";
    std::cin >> petName;
    PrintUtility::cleanScreen();

    player->setName(playerName);
    player->setSteps(0);

    Pet* pet;
    int petType = choosePetScreen();

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

int main()
{
    Menu print;
    print.menuScreen();
    print.mainMenu();
    //print.chooseSave();
    //print.choosePetScreen();
    // print.mainScreen();
    print.deathScreen();


    return 0;
}