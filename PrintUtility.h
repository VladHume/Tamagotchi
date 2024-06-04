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
static const int INDENT = 10;
static const std::string startBanner = "pictures\\banners\\start.txt";
static const std::string endBanner = "pictures\\banners\\end.txt";

class PrintUtility
{
private:
public:    
    static void cleanScreen();
    static int charCounter(std::string text);
    static void showPetStats(Player *player);
    static void showPetInfo(Player *player);
    static std::string drawStats(int variable);
    static std::string drawLine(int lenght);

};

#endif
