#include "FileUtility.h"

#include <cstdio>
#include <iostream>
#include <filesystem>

const std::string fileDirectory = ".\\saves";

// Constructor for the FileUtility class
FileUtility::FileUtility(std::string fName) : fileName(fName) {}

// Creates a new file in the specified directory or returns an existing file
FileUtility* FileUtility::createFile(const std::string& fileName) {
    // Construct the full file path
    std::string filePath = fileDirectory + "\\" + fileName;

    // Check if the file already exists
    if (!std::filesystem::exists(filePath)) {
        // If the file does not exist, create it
        std::ofstream f(filePath);
        if (f.is_open()) {
            FileUtility* newFile = new FileUtility(fileName);
            f.close(); // Close the file
            return newFile;
        } else {
            return nullptr; // Return null if the file could not be opened
        }
    } else {
        return new FileUtility(fileName); // Return a new FileUtility object if the file already exists
    }
}

// Deletes a file
bool FileUtility::deleteFile(const std::string& fileName) {
    // Attempt to remove the file and return true if successful, false otherwise
    if (std::remove((fileDirectory + "\\" + fileName).c_str()) != 0) {
        return false;
    } else {
        return true;
    }
}

// Updates the file with player data and current time
void FileUtility::updateFile(Player* player, const std::tm& currentTime) {
    json j;
    j["name"] = player->getName();
    j["playerSteps"] = player->getSteps();

    // Populate pet data
    json petData;
    petData["type"] = player->getPet()->getType();
    petData["name"] = player->getPet()->getName();
    petData["attention"] = player->getPet()->getAttention();
    petData["health"] = player->getPet()->getHealth();
    petData["cleanliness"] = player->getPet()->getCleanliness();
    petData["rested"] = player->getPet()->getRested();
    petData["satiated"] = player->getPet()->getSatiated();
    petData["isAlive"] = player->getPet()->getIsAlive();

    j["pet"] = petData;

    // Populate time data
    json timeData;
    timeData["year"] = currentTime.tm_year + 1900;  // tm_year is counted from 1900
    timeData["month"] = currentTime.tm_mon + 1;     // tm_mon starts from 0 for January
    timeData["day"] = currentTime.tm_mday;
    timeData["hour"] = currentTime.tm_hour;
    timeData["minute"] = currentTime.tm_min;
    timeData["second"] = currentTime.tm_sec;

    j["timeEndGame"] = timeData;

    // Write to the file
    std::ofstream file((fileDirectory + "\\" + fileName), std::ofstream::trunc);
    if (file.is_open()) {
        file << std::setw(4) << j << std::endl;
        file.close();
    }
}

// Reads data from the file and updates the player object
void FileUtility::read(Player* player) {
    std::ifstream file(fileDirectory + "\\" + fileName);
    if (file.is_open()) {
        json j;
        file >> j;

        player->setName(j["name"]);
        player->setSteps(j["playerSteps"]);

        // Populate pet data
        Pet* pet;
        json petData = j["pet"];
        std::string petType = petData["type"];
        if (petType == "DOG") {
            pet = new Dog();
        } else {
            pet = new Cat();
        }
        pet->setName(petData["name"]);
        pet->setAttention(petData["attention"]);
        pet->setHealth(petData["health"]);
        pet->setCleanliness(petData["cleanliness"]);
        pet->setRested(petData["rested"]);
        pet->setSatiated(petData["satiated"]);
        pet->setIsAlive(petData["isAlive"]);

        player->setPet(pet);

        file.close();
    }
}

// Prints the content of the file to the console
bool FileUtility::printFileContent(const std::string& filePath) {
    std::ifstream file(filePath); 
    if (!file.is_open()) { 
        return false; // Return false if the file could not be opened
    }

    std::string line;
    while (std::getline(file, line)) { 
        std::cout << line << std::endl;
    }

    file.close();
    return true;
}

// Reads the end game time from the file and returns it as a std::tm object
std::tm FileUtility::readTimeEndGame() {
    std::tm timeEndGame = {};

    std::ifstream file((fileDirectory + "\\" + fileName));
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();

        if (j.contains("timeEndGame")) {
            json timeData = j["timeEndGame"];
            timeEndGame.tm_year = timeData["year"].get<int>() - 1900;
            timeEndGame.tm_mon = timeData["month"].get<int>() - 1;
            timeEndGame.tm_mday = timeData["day"].get<int>();
            timeEndGame.tm_hour = timeData["hour"].get<int>();
            timeEndGame.tm_min = timeData["minute"].get<int>();
            timeEndGame.tm_sec = timeData["second"].get<int>();
        }
    } else {
        std::cerr << "Unable to open file: " << (fileDirectory + "\\" + fileName) << std::endl;
    }

    return timeEndGame;
}

// Returns a vector of files in the "saves" directory
std::vector<std::string> FileUtility::fileList() {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(fileDirectory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

// Returns a vector of files in the specified directory
std::vector<std::string> FileUtility::fileList(const std::string directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

// Reads frames from files in the specified directory and links them into a circular linked list
Frames* FileUtility::readFrames(const std::string directory) {
    std::vector<std::string> fileNames = FileUtility::fileList(directory);

    if (fileNames.empty()) {
        return nullptr; // Return null if no files are found
    }

    Frames* headFrame = nullptr; 
    Frames* currentFrame = nullptr; 

    for (const auto& fileName : fileNames) {
        std::ifstream file(directory + "\\" + fileName);
        if (!file.is_open()) {
            if (headFrame != nullptr) {
                delete headFrame;
            }
            return nullptr; // Return null if a file could not be opened
        }

        Frames* frame = new Frames();
        if (headFrame == nullptr) {
            headFrame = frame; // Set the first frame as headFrame
        } else {
            currentFrame->next = frame; // Link the current frame to the new frame
        }
        currentFrame = frame;

        std::string line;
        while (std::getline(file, line)) {
            currentFrame->frame.push_back(line); // Add lines to the frame
        }

        file.close();
    }
    currentFrame->next = headFrame; // Make the linked list circular

    return headFrame;
}

// Creates a unique file name based on player and pet information
std::string FileUtility::createFileName(Player *player) {
    std::string fileName = player->getName() + player->getPet()->getType() + player->getPet()->getName();
    if(checkFileExistence(fileName + ".json")) {
        int i = 1;
        while(checkFileExistence(fileName + std::to_string(i) + ".json")) {
            ++i;
        }
        return fileName + std::to_string(i) + ".json"; // Append a number to the file name if it already exists
    }
    return fileName + ".json";
}

// Checks if a file exists in the directory
bool FileUtility::checkFileExistence(const std::string& fileName) {
    return std::filesystem::exists(fileDirectory + "\\" + fileName);
}

// Returns the file name
std::string FileUtility::getFileName() {
    return fileName;
}
