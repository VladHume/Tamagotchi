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

//void FileUtility::updateFile(Player &player);

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
