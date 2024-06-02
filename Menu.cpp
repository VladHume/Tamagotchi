// #include "Menu.h"
// #include "PrintUtility.h"
// std::ostream & setColor(std::ostream &stream)
// {
//     stream << "\x1b[1;32m";
//     return stream;
// }

// std::ostream & unsetColor(std::ostream &stream)
// {
//     stream << "\x1b[1;37m";
//     return stream;
// }

// int Menu::readControlKeys()
// {
//     int userKey = 0;
//     system("stty raw");
//     while (true)
//     {
//         userKey = getchar(); 
//         if(isCorrectControlKey(userKey))
//         {
//             break;     
//         }      
//     }
//     system("stty cooked");
//     return userKey;
// }

// bool Menu::isCorrectControlKey(int key) 
// { 
//     return key == ENTER || key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_RIGHT;
// }


// void Menu::displayVert(const std::vector<std::string>& opt, int maxLen)
// {
//     PrintUtility::cleanScreen(); 
//     PrintUtility::startGame();
//     std::cout << PrintUtility::drawLine(maxLen);
//     for (int i = 0; i < static_cast<int>(opt.size()); i++)
//     {
//         int spaces = (maxLen - (PrintUtility::charCounter(opt[i])/2))-2;
//         if (i == currentOption)
//         {
//             std::cout << "| " << setColor << opt[i] << " ■" << unsetColor << std::right << std::setw(spaces-2) << std::setfill(' ') << "|" << std::endl;
//         }
//         else std::cout << "| " << opt[i] << std::right << std::setw(spaces) << std::setfill(' ') << "|" << std::endl;
//     }
//     std::cout << PrintUtility::drawLine(maxLen);
// }

// void Menu::displayHoriz(const std::vector<std::string>& opt, int maxLen)
// {
//     PrintUtility::cleanScreen();
//     std::cout << PrintUtility::drawLine(maxLen);
//     for (int i = 0; i < static_cast<int>(opt.size()); i++)
//     {
//         if (i == currentOption)
//         {
//             std::cout << setColor << opt[i] << " ■" << unsetColor;
//         }
//         else
//         {
//             std::cout << opt[i];
//         }
//         std::cout << std::setw(LINE_BETWEEN) << std::setfill(' ');
//     }
//     std::cout << '\n' << PrintUtility::drawLine(maxLen);
// }

// int Menu::chooseVertOption(const std::vector<std::string>& opt, int maxLen)
// {
    
//     currentOption = 0;
//     int numOptions = opt.size();
//     while (true)
//     {
//         displayVert(opt, maxLen);
//         int key = readControlKeys();
//         switch (key)
//         {
//             case ARROW_UP:
//                 currentOption = (currentOption - 1 + numOptions) % numOptions;
//                 break;
//             case ARROW_DOWN:
//                 currentOption = (currentOption + 1) % numOptions;
//                 break;
//             case ENTER:
//                 return currentOption; 
//             default:
//                 break;
//         }
//     }
// }

// int Menu::chooseYesNo(const std::vector<std::string>& opt, int maxLen)
// {
//     currentOption = 0; 
//     while (true)
//     {
//         displayHoriz(opt, maxLen);
//         int key = readControlKeys();
//         switch (key)
//         {
//             case ARROW_LEFT:
//                 currentOption = 0;
//                 break;
//             case ARROW_RIGHT:
//                 currentOption = 1;
//                 break;
//             case ENTER:
//                 return currentOption;
//             default:
//                 break;
//         }
//     }
// }

// void Menu::interactWithPet(Player* player)
// {
    
//     std::string petName = player->getPet()->getName();
//     int playerChoice = chooseVertOption(petOptions, SCREEN_WIDGHT);
//     std::cin.clear();
//     switch (playerChoice)
//     {
//     case 0: //Погодувати улюбленця
//         player->getPet()->feed();
//         std::cout << petName << " погодовано\n";
//         break;
//     case 1: //Полікувати улюбленця
//         player->getPet()->treat();
//         std::cout << petName << " поліковано\n";
//         break;
//     case 2: //Покупати улюбленця
//         player->getPet()->clean();
//         std::cout << petName << " покупано\n";
//         break;
//     case 3: //Погратися з улюбленцем
//         player->getPet()->play();
//         std::cout << "Ви погралися з "<< petName << '\n';
//         break;
//     case 4: //Погладити улюбленця
//         player->getPet()->pet();
//         std::cout << "Ви погладили "<< petName << '\n';    
//         break;
//     case 5: //Вдарити улюбленця
//         player->getPet()->punch();
//         std::cout << "Ви вдарили "<< petName << '\n';    
//         break;
//     case 6: // Покласти спати
//         player->getPet()->goToSleep();
//         std::cout << petName << " заснув\n";    
//         break;                    
//     default:
//         break;
//     }
// }


