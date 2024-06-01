#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <string>
#include "Player.h"
#include "Pet.h"
#include "Dog.h"
#include "Cat.h"
#include <vector>
#include <fstream>
#include "json\single_include\nlohmann\json.hpp"

using json = nlohmann::json;

class FileUtility {
private:
    std::string fileName;
public:
    FileUtility(std::string fileName);
    static FileUtility* createFile(const std::string& fileName);
    static bool deleteFile(const std::string& fileName);
    void updateFile(Player *player, const std::tm& currentTime);
    void read(Player* player);
    std::tm readTimeEndGame();
    static bool printFileContent(const std::string& filePath);
    static std::vector<std::string> fileList();
    static bool checkFileExistence(const std::string& fileName);
};

#endif 