#include "FileUtility.h"

#include <cstdio>
#include <iostream>
#include <filesystem>

const std::string fileDirectory = ".\\saves";

FileUtility::FileUtility(std::string fName) : fileName(fName) {}

//Створює новий файл у вказаній директорії, або повертає вже існуючиий файл
FileUtility* FileUtility::createFile(const std::string& fileName){
    std::string filePath = fileDirectory + "\\" + fileName;
    if (!std::filesystem::exists(filePath)) {
        std::ofstream f(filePath);
        if (f.is_open()) {
            FileUtility* newFile = new FileUtility(fileName);
            f.close();
            return newFile;
        } else {
            return nullptr;
        }
    } else {
        return new FileUtility(fileName);
    }
}

//Видаляє файл
bool FileUtility::deleteFile(const std::string& fileName){
    if (std::remove((fileDirectory + "\\" + fileName).c_str()) != 0) {
        return false;
    } else {
        return true;
    }
}

//Оновлює файл
void FileUtility::updateFile(Player* player, const std::tm& currentTime) {
    json j;
    j["name"] = player->getName();
    j["playerSteps"] = player->getSteps();

    json petData;
    petData["type"] = player->getPet()->getType();
    petData["name"] = player->getPet()->getName();
    petData["attention"] = player->getPet()->getAttention();
    petData["health"] = player->getPet()->getHealth();
    petData["cleanliness"] = player->getPet()->getCleanliness();
    petData["rested"] = player->getPet()->getRested();
    petData["satiated"] = player->getPet()->getSatiated();
    petData["isAlive"] = player->getPet()->getIsAlive();
    petData["lives"] = player->getPet()->getLives();

    j["pet"] = petData;

    json timeData;
    timeData["year"] = currentTime.tm_year + 1900;  // tm_year відраховується від 1900
    timeData["month"] = currentTime.tm_mon + 1;     // tm_mon починається з 0 для січня
    timeData["day"] = currentTime.tm_mday;
    timeData["hour"] = currentTime.tm_hour;
    timeData["minute"] = currentTime.tm_min;
    timeData["second"] = currentTime.tm_sec;

    j["timeEndGame"] = timeData;

    std::ofstream file((fileDirectory + "\\" + fileName), std::ofstream::trunc);
    if (file.is_open()) {
        file << std::setw(4) << j << std::endl;
        file.close();
    }
}

//Зчитує данні з файлу
void FileUtility::read(Player* player) {
    std::ifstream file(fileDirectory + "\\" + fileName);
    if (file.is_open()) {
        json j;
        file >> j;

        player->setName(j["name"]);
        player->setSteps(j["playerSteps"]);

        Pet* pet;
        json petData = j["pet"];
        std::string petType = petData["type"];
        if (petType == "DOG") {
            pet = new Dog();
        } else {
            pet = new Cat();
        } 
        // player->getPet()->setLives(5); 
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

bool FileUtility::printFileContent(const std::string& filePath) {
    std::ifstream file(filePath); 
    if (!file.is_open()) { 
        return false;
    }

    std::string line;
    while (std::getline(file, line)) { 
        std::cout << line << std::endl;
    }

    file.close();
    return true;
}

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


//Повертає вектор з файлами, які містяться у папці saves
std::vector<std::string> FileUtility::fileList() {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(fileDirectory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

//Повертає вектор з файлами, які містяться у директорії
std::vector<std::string> FileUtility::fileList(const std::string directory) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

Frames* FileUtility::readFrames(const std::string directory){
    std::vector<std::string> fileNames = FileUtility::fileList(directory);

    if (fileNames.empty()) {
        return nullptr;
    }

    Frames* headFrame = nullptr; 
    Frames* currentFrame = nullptr; 

    for (const auto& fileName : fileNames) {
        std::ifstream file(directory + "\\" + fileName);
        if (!file.is_open()) {
            if (headFrame != nullptr) {
                delete headFrame;
            }
            return nullptr;
        }

        Frames* frame = new Frames();
        if (headFrame == nullptr) {
            headFrame = frame;
        } else {
            currentFrame->next = frame; 
        }
        currentFrame = frame;

        std::string line;
        while (std::getline(file, line)) {
            currentFrame->frame.push_back(line);
        }

        file.close();
    }
    currentFrame->next = headFrame;

    return headFrame;
}

std::string FileUtility::createFileName(Player *player){
    std::string fileName = player->getName() + player->getPet()->getType() + player->getPet()->getName();
    if(checkFileExistence(fileName)){
        int i = 1;
        while(checkFileExistence(fileName + std::to_string(i))){
            i++;
        }
        return fileName + std::to_string(i) + ".json";
    }
    return fileName + ".json";
}

//Перевіряє наявність файлу у директорії
bool FileUtility::checkFileExistence(const std::string& fileName) {
    return std::filesystem::exists(fileDirectory + "\\" + fileName);
}

std::string FileUtility::getFileName(){
    return fileName;
}
