#include <iostream>
#include "Cat.h"
#include "FileUtility.h"

Cat::Cat(std::string name) :  Pet(name, FileUtility::readFrames(happyPath),  FileUtility::readFrames(sadPath), FileUtility::readFrames(usualPath), FileUtility::readFrames(sleepPath), FileUtility::readFrames(deathPath)){}
Cat::Cat():Pet(){
    happy_ = FileUtility::readFrames(happyPath);
    sad_ = FileUtility::readFrames(sadPath);
    usual_ = FileUtility::readFrames(usualPath);
    sleep_ = FileUtility::readFrames(sleepPath);
    death_ = FileUtility::readFrames(deathPath);
}

std::string Cat::getType(){
    return std::string("CAT"); 
}


