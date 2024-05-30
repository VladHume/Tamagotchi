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
void FileUtility::updateFile(Player* player) {
    json j;
    j["name"] = player->getName();
    j["playerSteps"] = player->getSteps();

    json petData;
    petData["type"] = player->getPet()->getType();
    petData["name"] = player->getPet()->getPetName();
    petData["attention"] = player->getPet()->getAttention();
    petData["health"] = player->getPet()->getHealth();
    petData["cleanliness"] = player->getPet()->getCleanliness();
    petData["rested"] = player->getPet()->getRested();
    petData["satiated"] = player->getPet()->getSatiated();
    petData["isAlive"] = player->getPet()->getIsAlive();

    j["pet"] = petData;

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
        } else if (petType == "CAT") {
            pet = new Cat();
        } else {
            return;
        }

        pet->setPetName(petData["name"]);
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

//Повертає вектор з файлами, які містяться у директорії
std::vector<std::string> FileUtility::fileList() {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(fileDirectory)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

//Перевіряє наявність файлу у директорії
bool FileUtility::checkFileExistence(const std::string& fileName) {
    std::ifstream file(fileDirectory + "\\" + fileName);
    return file.good();
}