#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <string>
#include "Player.h"

class FileUtility {
private:
    std::string fileName;
    std::string fileDirectory;

public:
    FileUtility(const std::string& fileName);
    static FileUtility createFile(const std::string& fileName);
    static bool deleteFile(const std::string& fileName);
    void updateFile(Player &player);
};

#endif