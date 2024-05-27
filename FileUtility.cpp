#include "FileUtility.h"

#include <cstdio>
#include <iostream>
#include <filesystem>

const std::string fileDirectory = ".\\saves";

FileUtility::FileUtility(std::ofstream &f) : file(f) {}

FileUtility::~FileUtility() {
    if (file.is_open()) {
        file.close();
    }
}

FileUtility* FileUtility::createFile(const std::string& fileName){
    std::ofstream f(fileDirectory + "\\" + fileName);
    if (f.is_open()) {
        FileUtility* newFile = new FileUtility(f);
        f.close();
        return newFile;
    } else {
        return nullptr;
    }
}


bool FileUtility::deleteFile(const std::string& fileName){
    if (std::remove((fileDirectory + "\\" + fileName).c_str()) != 0) {
        return false;
    } else {
        return true;
    }
}

void FileUtility::updateFile(Player* player) {
    if (!file) {
        return;
    }

    // Запис полів Player
    int playerSteps = player->getSteps();
    std::string playerName = player->getName();

    file.write(reinterpret_cast<const char*>(&playerSteps), sizeof(playerSteps));
    writeString(file, playerName);

    // Запис полів Pet
    int attention = player->getPet()->getAttention();
    int health = player->getPet()->getHealth();
    int cleanliness = player->getPet()->getCleanliness();
    int fatigue = player->getPet()->getFatigue();
    int hunger = player->getPet()->getHunger();
    std::string petName = player->getPet()->getName();
    bool isAlive = player->getPet()->getIsAlive();

    file.write(reinterpret_cast<const char*>(&attention), sizeof(attention));
    file.write(reinterpret_cast<const char*>(&health), sizeof(health));
    file.write(reinterpret_cast<const char*>(&cleanliness), sizeof(cleanliness));
    file.write(reinterpret_cast<const char*>(&fatigue), sizeof(fatigue));
    file.write(reinterpret_cast<const char*>(&hunger), sizeof(hunger));
    writeString(file, petName);
    file.write(reinterpret_cast<const char*>(&isAlive), sizeof(isAlive));
}

void writeString(std::ofstream &out, const std::string &str) {
    size_t length = str.length();
    out.write(reinterpret_cast<const char*>(&length), sizeof(length));
    out.write(str.c_str(), length);
}

std::vector<std::string> FileUtility::fileList() {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(fileDirectory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

bool FileUtility::checkFileExistence(const std::string& fileName) {
    std::ifstream file(fileDirectory + "\\" + fileName);
    return file.good();
}

int main() {
    // Створення об'єкта Pet
    Dog* myDog = new Dog("Buddy");

    // Створення об'єкта Player
    Player player("John", myDog, 100);

    FileUtility *fileUtility = FileUtility::createFile("test.bin");
    // Запис об'єкта Player у файл
    fileUtility->updateFile(&player);


    std::cout << "Дані гравця та його вихованця були записані у файл." << std::endl;

    return 0;
}