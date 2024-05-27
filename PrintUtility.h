#ifndef PRINTUTILITY_H
#define PRINTUTILITY_H
#include <fstream>
#include <iostream>
#include <iomanip>

class PrintUtility
{
private:
    Player *player;
    Menu *menu;

public:
    static void cleanScreen();
    static void drawMainScreen();
    static void drawPetChoice();
    static void drawEndGame();
};


#endif