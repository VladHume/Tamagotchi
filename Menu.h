#ifndef MENU_H
#define MENU_H
#include <vector>
#include <string>
#include <iostream>
enum MainMenuChoice
{
    START = 1,
    LOAD = 2,
    EXIT = 3
};

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
    int currentOption = 0; 
    int numOptions; 
    std::vector<std::string> petOptions {"Погодувати", "Полікувати", "Покупати", "Погратися",
                                     "Погладити", "Вдарити", "Покласти спати"}; 
    //std::vector<std::string> yesNoOptions {"Так", "Ні"};
    //std::vector<std::string> yesNoOptions {"Почати нову гру", "Завантажити збереження", "Вийти з гри"};
public:
    const std::vector<std::string>& getPetOptions() const;
    bool isCorrectControlKey(int key);
    int readControlKeys();
    int chooseOption(const std::vector<std::string>& opt); 
    void displayOptions();
};

#endif
