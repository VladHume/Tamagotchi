#ifndef FILEUTILITY_H
#define FILEUTILITY_H

#include <string>
#include "Player.h"
#include "Pet.h"
#include "Dog.h"
#include "Cat.h"
#include "Frames.h"
#include <vector>
#include <fstream>
#include "json\single_include\nlohmann\json.hpp"

using json = nlohmann::json;

class FileUtility {
private:
    // Name of the file to be managed
    std::string fileName;

public:
    // Constructor that initializes the FileUtility with a given file name
    FileUtility(std::string fileName);

    // Static method to create a new file in the specified directory, or return an existing file
    static FileUtility* createFile(const std::string& fileName);

    // Static method to delete a file in the specified directory
    static bool deleteFile(const std::string& fileName);

    // Method to update the file with player's current state and the current time
    void updateFile(Player *player, const std::tm& currentTime);

    // Method to read the player's state from the file
    void read(Player* player);

    // Method to read the end game time from the file
    std::tm readTimeEndGame();

    // Static method to print the content of a file to the console
    static bool printFileContent(const std::string& filePath);

    // Static method to return a vector of file names in the default directory
    static std::vector<std::string> fileList();

    // Static method to return a vector of file names in the specified directory
    static std::vector<std::string> fileList(const std::string directory);

    // Static method to check if a file exists in the specified directory
    static bool checkFileExistence(const std::string& fileName);

    // Static method to read frames from files in the specified directory and return a linked list of Frames
    static Frames* readFrames(const std::string directory);

    // Static method to create a unique file name based on the player's and pet's information
    static std::string createFileName(Player *player);

    // Method to get the name of the file being managed by this instance
    std::string getFileName();
};


#endif 