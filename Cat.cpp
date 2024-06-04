#include <iostream>
#include "Cat.h"
#include "FileUtility.h"

Cat::Cat(std::string name) :  Pet(name, FileUtility::readFrames(happyPath),  FileUtility::readFrames(sadPath), FileUtility::readFrames(usualPath), FileUtility::readFrames(sleepPath), FileUtility::readFrames(deathPath)){
    lives_ = 9;
}
Cat::Cat():Pet(){
    happy_ = FileUtility::readFrames(happyPath);
    sad_ = FileUtility::readFrames(sadPath);
    usual_ = FileUtility::readFrames(usualPath);
    sleep_ = FileUtility::readFrames(sleepPath);
    death_ = FileUtility::readFrames(deathPath);
    lives_ = 9;
}

bool Cat::death (){
    if (health_ <= 0 || rested_ <= 0 || satiated_ <= 0) {
        if (lives_ <= 0) {
            isAlive_ = false;
            return true;
        } else {
            health_ = 30;
            cleanliness_ = 30;
            rested_ = 30;
            satiated_ = 30;
            lives_--;
            return false;
        }
    }
    return false;
}

std::string Cat::getType(){
    return std::string("CAT"); 
}


