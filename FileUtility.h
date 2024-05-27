#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <string>
#include "Player.h"
#include "Dog.h"
#include "Cat.h"
#include <vector>
#include <fstream>

class FileUtility {
private:
    std::ofstream &file;
    //const std::string fileDirectory;
    void writeString(std::ofstream &out, const std::string &str);
public:
    FileUtility(std::ofstream &f);
    ~FileUtility();
    static FileUtility* createFile(const std::string& fileName);
    static bool deleteFile(const std::string& fileName);
    void updateFile(Player *player);
    static std::vector<std::string> fileList();
    static bool checkFileExistence(const std::string& fileName);
};

#endif 