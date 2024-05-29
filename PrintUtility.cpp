#include "PrintUtility.h"
const std::string PrintUtility::sbannerFile = "pictures\\banners\\start.txt";
const std::string PrintUtility::ebannerFile = "pictures\\pet\\cat\\usualCat\\Cat1.txt";
class Menu;
void PrintUtility::cleanScreen()
{
    system("clear");
}

int PrintUtility::charCounter(std::string text)
{
    int count = 0;
    for (int i = 0; text[i]; i++)
    {
        if (text[i] == ' ') count++;
        count++;  
    } 
    return count;
}

// void PrintUtility::startGame()
// {
//     std::string enterLine = "Натисніть Enter щоб розпочати гру";
//     std::string bannerInput;
//     cleanScreen();
//     std::ifstream startBanner(sbannerFile);
//     if (!startBanner) throw std::runtime_error("Error: could not open file " + sbannerFile);
//     startBanner.unsetf(std::ios::skipws);
//     while (!startBanner.eof())
//     {
//         getline(startBanner, bannerInput);
//         std::cout << bannerInput << '\n';
//     } 
//     std::cout << drawLine() << '\n';
//     std::cout << center(enterLine, SCREEN_SIZE) << '\n';
//     std::cout << drawLine() << '\n';
// }

std::string PrintUtility::drawLine(int lenght)
{
    return std::string(lenght, '-') + "\n";
}

// int main()
// {
//     PrintUtility::startGame();
//     return 0;
// }