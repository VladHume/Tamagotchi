#ifndef PRINTUTILITY_H
#define PRINTUTILITY_H
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "Player.h"
#include "Menu.h"

class PrintUtility
{
private:
    Player *player;
    // Menu *menu;
    static const std::string sbannerFile;
    static const std::string ebannerFile;
public:    
    static const int LINE_SIZE = 40;
    static void cleanScreen();
    static int charCounter(std::string text);
    static void mainScreen();
    static void petChoice();
    static void startGame();
    static void endGame();
    static std::string drawLine(int lenght);
};

#endif
