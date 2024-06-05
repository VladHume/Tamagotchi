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
static const int BETWEEN_LINES = 15;
static const int LIMIT_FOR_INPUT = 25;
static const int MAX_LEFT_INFO = 47;
static const int TIME_SPACE = 10;
//pics for start and end game
static const std::string startBanner = "pictures\\banners\\start.txt";
static const std::string endBanner = "pictures\\banners\\end.txt";
//icons for choose pet
static const std::string chooseCatPic = "pictures\\icons\\CatIcon.txt";
static const std::string chooseDogPic = "pictures\\icons\\DogIcon.txt";
//text when you enter pet's and player's game
static const std::string welcomeText = "data\\welcometext.txt";

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
    static std::string limitedInput(const std::string& input, size_t maxLength); 

};

#endif
