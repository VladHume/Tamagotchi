#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "PrintUtility.h"
#include "FileUtility.h"
#include "TimeControl.h"
#include "Player.h"

static const int MENU_WIDGHT = 40;
static const int LINE_BETWEEN = 20;
static const int INDENT = 10;

enum ControlKeys
{
    ENTER = 13,
    ARROW_UP = 65,
    ARROW_DOWN = 66,  
    ARROW_LEFT = 68,
    ARROW_RIGHT = 67
};

class Menu
{
private:
    Player *player;
    int currentOption; 
    int numOptions;   
    bool isMainScreen = true;  
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати", "Вийти в головне меню"}; 
    std::vector<std::string> menuOptions {"Почати нову гру", "Завантажити збереження", "Вийти з гри"};
    void displayVert(const std::vector<std::string>& opt, int maxLen, Player* player);
    int readControlKeys();
    bool isCorrectControlKeys(int key);
public:
    Menu();
    ~Menu();
    int chooseVertOption(const std::vector<std::string>& opt, int maxLen, Player* player);
    void interactWithPet(Player* player);
    void mainScreen();
    void menuScreen();
    void choosePetScreen();
    void savesScreen();
    
};

#endif
