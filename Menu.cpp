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

// Set green for selected option
std::ostream & setColor(std::ostream &stream)
{
    stream << "\x1b[1;32m";
    return stream;
}

// Unset green
std::ostream & unsetColor(std::ostream &stream)
{
    stream << "\x1b[1;37m";
    return stream;
}

// A function to read input in raw mode
int Menu::readControlKeys()
{
    int userKey = 0;
    // Enter raw mode
    system("stty raw");
    while (true)
    {
        userKey = getchar(); 
        if (isCorrectControlKeys(userKey))
        {
            break;     
        }      
    }
    // Exit raw mode
    system("stty cooked");
    return userKey;
}

bool Menu::getIsMainScreen() {
    return isMainScreen;
}

// All keys user need to use and its validation
bool Menu::isCorrectControlKeys(int key) 
{ 
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN;
}

// Display options in the menu
void Menu::displayOptions(const std::vector<std::string>& options)
{
    std::cout << PrintUtility::drawLine(SCREEN_WIDTH);
    for (const auto& option : options)
    {
        int spaces = (SCREEN_WIDTH - PrintUtility::charCounter(option)) - 2;
        if (&option == &options[currentOption])
        {
            // Display selected option
            std::cout << strBar << ' ' << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces - 2) << strBar << std::endl;
        }
        else
        {
            // Display unselected option
            std::cout << strBar << ' ' << option << std::right << std::setw(spaces) << std::setfill(' ') << strBar << std::endl;
        }
    }
    std::cout << PrintUtility::drawLine(SCREEN_WIDTH);
}

// Display the main screen
void Menu::displayMainScreen(Player *player)
{
    PrintUtility::cleanScreen(); 
    player->getPet()->drawPet();
    PrintUtility::showPetStats(player);
    std::cout << PrintUtility::drawLine(SCREEN_WIDTH);
    PrintUtility::showPetInfo(player);
    displayOptions(petOptions);
}

// Display the choose pet screen
void Menu::displayChoosePetScreen()
{
    PrintUtility::cleanScreen();
    const std::string CHOOSE_PET = "|  Оберіть свого улюбленця!  |";
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(CHOOSE_PET)) / 2) << " "  << PrintUtility::drawLine(PrintUtility::charCounter(CHOOSE_PET));
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(CHOOSE_PET)) / 2) << " "  << CHOOSE_PET << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(CHOOSE_PET)) / 2) << " "  << PrintUtility::drawLine(PrintUtility::charCounter(CHOOSE_PET));
    std::cout << '\n' << PrintUtility::drawLine(SCREEN_WIDTH);
    
    int index = 0;
    for (const auto& option : choosePetOptions)
    {
        int spaces = (SCREEN_WIDTH - PrintUtility::charCounter(option) - 2);
        if (index == currentOption)
        {  
            // Display selected option
            std::cout << strBar << ' ' << setColor << option << " ■" << unsetColor << std::right << std::setw(spaces -2) << strBar << std::endl;
            if (index == 0)
            {
                FileUtility::printFileContent(chooseDogPic);
            }
            else
            {
                FileUtility::printFileContent(chooseCatPic);
            }
            std::cout << PrintUtility::drawLine(SCREEN_WIDTH);
        }
        else 
        {
            // Display unselected option
            std::cout << strBar << ' ' << option << std::right << std::setw(spaces) << strBar << std::endl;
            std::cout << PrintUtility::drawLine(SCREEN_WIDTH);
        }
        ++index;
    }
}

// Display the menu screen
void Menu::displayMenuScreen()
{
    PrintUtility::cleanScreen();
    displayOptions(menuOptions);
}

// Main function to determine what the user has entered
int Menu::chooseVertOption(Player *player, displayVarients a, std::vector<std::string> &opt)
{
    int numOptions = opt.size();
    currentOption = currentOption % numOptions;
    while (true)
    {
        switch (a)
        {
            case FULL_SCREEN:
                displayMainScreen(player);
                break;
            case PART_SCREEN:
                displayChoosePetScreen();
                break;
            case FILE_SCREEN:
                displayFileScreen();
                break;
            case MAIN_SCREEN:
                displayMenuScreen();
                break;
            default:
                std::cerr << "Invalid extension" << std::endl;
                break;
        }

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

int Menu::choosePetScreen()
{
    return chooseVertOption(player, PART_SCREEN, choosePetOptions);
}

void Menu::interactWithPet(Player* player)
{
    std::string petName = player->getPet()->getName();
    int playerChoice = chooseVertOption(player, FULL_SCREEN, petOptions);
    std::cin.clear();

    switch (playerChoice)
    {
        case 0:
            player->getPet()->feed();
            break;
        case 1:
            player->getPet()->treat();
            break;
        case 2:
            player->getPet()->clean();
            break;
        case 3:
            player->getPet()->play();
            break;
        case 4:
            player->getPet()->pet();
            break;
        case 5:
            player->getPet()->punch();
            break;
        case 6:
            player->getPet()->goToSleep();
            break;
        case 7:
            isMainScreen = false; 
            mainMenu();
            return;                       
        default:
            break;
    }
    player->increasePlayerSteps();
}

void Menu::mainScreen(const std::string& fileName)
{
    Player player;
    FileUtility *fu = FileUtility::createFile(fileName);
    fu->read(&player);
    TimeControl tc(&player, fu, this);

    isMainScreen = true;
    while (isMainScreen)
    {
        interactWithPet(&player);
    }
}

void Menu::menuScreen()
{
    const std::string MENU_ENTER_TEXT = "|  Нажміть ENTER щоб почати гру..  |";
    PrintUtility::cleanScreen();
    FileUtility::printFileContent(startBanner);

    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(MENU_ENTER_TEXT))/2) << " " << PrintUtility::drawLine(PrintUtility::charCounter(MENU_ENTER_TEXT));
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(MENU_ENTER_TEXT))/2) << " " << MENU_ENTER_TEXT << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(MENU_ENTER_TEXT))/2) << " " << PrintUtility::drawLine(PrintUtility::charCounter(MENU_ENTER_TEXT));

    std::cin.get(); 
}

void Menu::deathScreen()
{
    const std::string MENU_EXIT_TEXT = "|  Нажміть ENTER щоб вийти..  |";
    PrintUtility::cleanScreen();
    FileUtility::printFileContent(endBanner);
    isGameRunning = false;

    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(MENU_EXIT_TEXT))/2) << " " << PrintUtility::drawLine(PrintUtility::charCounter(MENU_EXIT_TEXT));
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(MENU_EXIT_TEXT))/2) << " " << MENU_EXIT_TEXT << std::endl;
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(MENU_EXIT_TEXT))/2) << " " << PrintUtility::drawLine(PrintUtility::charCounter(MENU_EXIT_TEXT));

    std::cin.get(); 
}

void Menu::displayFileScreen()
{
    PrintUtility::cleanScreen();
    displayOptions(fileList);
}

void Menu::deleteSave()
{
    fileList = FileUtility::fileList();
    if (fileList.empty())
    {
        mainMenu();
        return;
    }
    int playerChoice = chooseVertOption(player, FILE_SCREEN, fileList);
    FileUtility::deleteFile(fileList[playerChoice]);
    fileList = FileUtility::fileList();
    mainMenu();
}

void Menu::chooseSave()
{
    fileList = FileUtility::fileList();
    if (fileList.empty())
    {
        mainMenu();
        return;
    }
    int playerChoice = chooseVertOption(player, FILE_SCREEN, fileList);
    mainScreen(fileList[playerChoice]);
}

void Menu::mainMenu()
{
    std::cin.clear();
    int playerChoice = chooseVertOption(player, MAIN_SCREEN, menuOptions);
    switch (playerChoice)
    {
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

void Menu::startNewGame()
{
    const std::string TEXT_NAME = "Введіть ім'я власника: ";
    const std::string TEXT_PETNAME = "Введіть ім'я улюбленця: ";
    PrintUtility::cleanScreen();
    std::string playerName;
    std::string petName;

    FileUtility::printFileContent(welcomeText);
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(TEXT_NAME))/2) << " " << TEXT_NAME;
    std::cin >> playerName;
    playerName = PrintUtility::limitedInput(playerName, LIMIT_FOR_INPUT);
    
    PrintUtility::cleanScreen();
    FileUtility::printFileContent(welcomeText);
    std::cout << std::right << std::setw((SCREEN_WIDTH - PrintUtility::charCounter(TEXT_PETNAME))/2) << " " << TEXT_PETNAME;
    std::cin >> petName;
    petName = PrintUtility::limitedInput(petName, LIMIT_FOR_INPUT);
    PrintUtility::cleanScreen();

    player->setName(playerName);
    player->setSteps(0);

    Pet* pet;
    int petType = choosePetScreen();

    if (choosePetOptions[petType] == "Собака")
    {
        pet = new Dog();
    }
    else if (choosePetOptions[petType] == "Кіт")
    {
        pet = new Cat();
    }
    else
    {
        return;
    }
    pet->setName(petName);
    player->setPet(pet);

    FileUtility* fileUtility = FileUtility::createFile(FileUtility::createFileName(player));
    std::time_t now = std::time(nullptr);
    std::tm currentTime = *std::localtime(&now);
    fileUtility->updateFile(player, currentTime);

    mainScreen(fileUtility->getFileName());
}
