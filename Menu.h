#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "PrintUtility.h"
#include "Pet.h"
#include "Player.h"
#include "Dog.h"

static const int SCREEN_WIDGHT = 76;
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
    int currentOption; 
    int numOptions;     
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати", "Вийти в головне меню"}; 
    std::vector<std::string> yesNoOptions {"Ні", "Так"};
    std::vector<std::string> menuOptions {"Почати нову гру", "Завантажити збереження", "Вийти з гри"};
public:
    const std::vector<std::string>& getPetOptions() const;
    const std::vector<std::string>& getYesNoOptions() const;
    const std::vector<std::string>& getMenuOptions() const;
    bool isCorrectControlKey(int key);
    int readControlKeys();
    void interactWithPet(Player* player);
    int chooseYesNo(const std::vector<std::string>& opt, int maxLen);
    int chooseVertOption(const std::vector<std::string>& opt, int maxLen); 
    void displayVert(const std::vector<std::string>& opt, int maxLen);
    void displayHoriz(const std::vector<std::string>& opt, int maxLen);
    void hovnotest();
    
};

#endif
