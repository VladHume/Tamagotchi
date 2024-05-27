#include "Menu.h"
const std::vector<std::string>& Menu::getPetOptions() const {
        return petOptions;
    }
int Menu::readControlKeys()
{
    int userKey = 0;
    system("stty raw");
    while (true)
    {
        userKey = getchar(); 
        if(isCorrectControlKey(userKey))
        {
            break;     
        }      
    }
    system("stty cooked");
    return userKey;
}

bool Menu::isCorrectControlKey(int key)
{
    return key == ENTER || key == ARROW_UP || key == ARROW_DOWN || key == ARROW_LEFT || key == ARROW_RIGHT;
}

// методя для демонстрації роботи
// void Menu::displayOptions()
// {
//     std::cout << "\033c"; 
//     numOptions = petOptions.size();
//     for (int i = 0; i < numOptions; ++i)
//     {
//         if (i == currentOption)
//         {
//             std::cout << petOptions[i] << " ■" << std::endl;
//         }
//         else
//         {
//             std::cout << petOptions[i] << std::endl;
//         }
//     }    
// }

int Menu::chooseOption(const std::vector<std::string>& opt)
{
    int numOptions = opt.size();
    while (true)
    {
        displayOptions();
        int key = readControlKeys();

        switch (key)
        {
            case ARROW_UP:
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case ARROW_DOWN:
                currentOption = (currentOption + 1) % numOptions;
                break;
            case ENTER:
                return currentOption;
            default:
                break;
        }
    }
}

int main()
{
    Menu menu;
    int choice = menu.chooseOption(menu.getPetOptions());
    std::cout << "You chose option: " << choice << std::endl;

    return 0;
}
