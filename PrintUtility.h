#ifndef PRINTUTILITY_H
#define PRINTUTILITY_H
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <thread>
#include <string>
#include "Player.h"
#include "Pet.h"
#include "FileUtility.h"
#include "TimeControl.h"

static const int SCREEN_WIDGHT = 76;
static const int MENU_WIDGHT = 40;
static const int LINE_BETWEEN = 20;

enum ControlKeys
{
    ENTER = 13,
    ARROW_UP = 65,
    ARROW_DOWN = 66,  
    ARROW_LEFT = 68,
    ARROW_RIGHT = 67
};
class PrintUtility
{
private:
    Player *player;
    // Menu *menu;
    int currentOption; 
    int numOptions; 
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати", "Вийти в головне меню"}; 
    std::vector<std::string> yesNoOptions {"Ні", "Так"};
    std::vector<std::string> menuOptions {"Почати нову гру", "Завантажити збереження", "Вийти з гри"};
public:    
    static void cleanScreen();
    static int charCounter(std::string text);
    void showPetStats(Player *player);
    void showPetInfo(Player *player);
    std::string drawStats(int variable);
    void mainScreen();
    static std::string drawLine(int lenght);
    void func(Player *player);
    //funcs from menu
     void interactWithPet(Player* player);
    int readControlKeys();
    bool isCorrectControlKeys(int key);
    void displayVert(const std::vector<std::string>& opt, int maxLen, Player *player);
    void displayHoriz(const std::vector<std::string>& opt, int maxLen) ;
    int chooseVertOption(const std::vector<std::string>& opt, int maxLen, Player *player);
    int chooseYesNo(const std::vector<std::string>& opt, int maxLen );


};

#endif
