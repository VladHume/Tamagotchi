#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "FileUtility.h"
#include "Player.h"

enum ControlKeys
{
    ENTER = 13,
    ARROW_UP = 65,  
    ARROW_DOWN = 66
};

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
    int currentOption; 
    int numOptions;   
    bool isMainScreen; 
    bool isGameRunning; 
    void displayMainScreen(Player* player);
    void displayChoosePetScreen();
    void displayFileScreen();
    void displayMenuScreen();
    int readControlKeys();
    bool isCorrectControlKeys(int key);
public:
    Menu();
    ~Menu();
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати", "Вийти в головне меню"}; 
    std::vector<std::string> menuOptions {"Почати нову гру", "Завантажити збереження", "Видалити збереження" ,"Вийти з гри"};
    std::vector<std::string> choosePetOptions {"Собака", "Кіт"};
    std::vector<std::string> fileList;
    
    int chooseVertOption(Player *player, displayVarients a, std::vector<std::string>& opt);
    void interactWithPet(Player* player);
    void mainScreen(std::string fileName);
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
