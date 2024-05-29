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
    static const int SCREEN_WIDGHT = 76;
    static const int LINE_BETWEEN_OPT = 40;
    int currentOption = 0; 
    int numOptions; 
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати", "Вийти в головне меню"}; 
    std::vector<std::string> yesNoOptions {"Так", "Ні"};
    std::vector<std::string> menuOptions {"Почати нову гру", "Завантажити збереження", "Вийти з гри"};
public:
    const std::vector<std::string>& getPetOptions() const;
    const std::vector<std::string>& getYesNoOptions() const;
    const std::vector<std::string>& getMenuOptions() const;
    bool isCorrectControlKey(int key);
    int readControlKeys();
    void interactWithPet(Player* player);
    int chooseVertOption(const std::vector<std::string>& opt, int maxLen); 
    void displayPetInteractions(const std::vector<std::string>& opt, int maxLen);
    
};

#endif
