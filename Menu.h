#ifndef MENU_H
#define MENU_H
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "FileUtility.h"
#include "Player.h"

//enum interaction with the console
enum ControlKeys
{
    ENTER = 13,
    ARROW_UP = 65,  
    ARROW_DOWN = 66
};

//Enum for different extensions
enum displayVarients
{
    FULL_SCREEN,
    PART_SCREEN,
    FILE_SCREEN,
    MAIN_SCREEN
};

class Menu
{
private:
    Player *player;
    int currentOption = 0; 
    int numOptions;   
    bool isMainScreen; 
    bool isGameRunning; 
    void displayMainScreen(Player* player);
    void displayChoosePetScreen();
    void displayFileScreen();
    void displayMenuScreen();
    void displayOptions(const std::vector<std::string>& options);
    int chooseVertOption(Player *player, displayVarients a, std::vector<std::string>& opt);
    int readControlKeys();
    bool isCorrectControlKeys(int key);
    const std::string startBanner = "pictures\\banners\\start.txt";
    const std::string endBanner = "pictures\\banners\\end.txt";
    const std::string chooseCatPic = "pictures\\icons\\CatIcon.txt";
    const std::string chooseDogPic = "pictures\\icons\\DogIcon.txt";
    const std::string welcomeText = "data\\welcometext.txt";
    const char strBar = '|';
    const int LIMIT_FOR_INPUT = 25;
    const int SCREEN_WIDTH = 76;

public:
    Menu();
    ~Menu();
    //vectors with options
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати", "Вийти в головне меню"}; 
    std::vector<std::string> menuOptions {"Почати нову гру", "Завантажити збереження", "Видалити збереження" ,"Вийти з гри"};
    std::vector<std::string> choosePetOptions {"Собака", "Кіт"};
    std::vector<std::string> fileList;

    void interactWithPet(Player* player);
    void mainScreen(const std::string& fileName);
    void menuScreen();
    void deathScreen();
    int choosePetScreen();
    void chooseSave();
    bool getIsMainScreen();
    void mainMenu();
    void startNewGame();
    void deleteSave();
};

#endif
