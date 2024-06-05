#include "Pet.h"
#include "Player.h"
#include "FileUtility.h"
#include <iostream>
#include <cstring>
#include <string>

//constructors
Pet::Pet(std::string name, Frames *happy, Frames *sad, Frames *usual, Frames *sleep, Frames *death): name_(name), attention_(60), health_(100), cleanliness_(60), rested_(90), satiated_(60) , isAlive_(true), currentMood_(MOOD::NORMAL), isAwaken_(true), happy_(happy), sad_(sad), usual_(usual), sleep_(sleep), death_(death){}

Pet::Pet(): name_(""), attention_(60), health_(100), cleanliness_(60), rested_(90), satiated_(60), 
isAlive_(true), currentMood_(MOOD::NORMAL), isAwaken_(true),  happy_(nullptr), sad_(nullptr),
usual_(nullptr), sleep_(nullptr), death_(nullptr) {}

//destructor
Pet::~Pet() {}

//getters
int  Pet::getAttention(){
    return attention_;
}
int Pet::getHealth(){
    return health_;
}
 int Pet::getCleanliness(){
    return cleanliness_;
 }

int Pet::getRested(){
    return rested_;
}

int Pet::getSatiated(){
    return satiated_;
}

std::string Pet::getName(){
        return name_;
}
bool Pet::getIsAlive(){
    return isAlive_;
}

MOOD Pet::getMood(){ 
  return currentMood_;
}

bool Pet::getIsAwaken(){
    return isAwaken_;
}

//method to get string a variable that represents the pet's mood
std::string Pet::getStringMood() {
    switch(currentMood_) {
        case MOOD::HAPPY:
            return "Щасливий"; 
        case MOOD::NORMAL:
            return "Спокійний";
        case MOOD::SAD:
            return "Невтішний";
        default:
            return " ";
    }
}

//setters
void Pet::setIsAlive(bool isAlive){
    isAlive_ = isAlive;
}

void Pet::setAttention(int attention){
    attention_ = attention;
    checkBounds();
}
void Pet::setHealth(int health){
    health_ = health;
    checkBounds();
}
void Pet::setCleanliness(int cleanliness){
    cleanliness_ = cleanliness;
    checkBounds();
}
void Pet::setRested(int rested){
    rested_ = rested;
    checkBounds();
}
void Pet::setSatiated(int satiated){
    satiated_ = satiated;
    checkBounds();
}

void Pet::setName(std::string name){
    name_ = name;
}

void Pet::setMood(MOOD mood){  //+
    currentMood_ = mood;
}

void Pet::setIsAwaken(bool isAwaken){
    isAwaken_ = isAwaken;
}

//method for feeding a pet
void Pet::feed() { 
     if (isAlive_) {
        wakeUp();
        satiated_ += 20;
        cleanliness_ -= 10;
        rested_ -= 10;
        health_ += 5;
        checkBounds();
     }
}

//a method for treating a pet
void Pet::treat(){ 
      if (isAlive_) {
        wakeUp();
        if(health_ < 90){
            health_ = 100;
            rested_ -= 10;
            checkBounds();
        }
    }
}

//method for cleaning a pet
void Pet::clean() {  
     if (isAlive_) {
        wakeUp();
        cleanliness_ += 30;
        rested_ -= 10;
        checkBounds();
    }
}

//method for playing with pet
void Pet::play(){ 
    if (isAlive_) {
        wakeUp();
        attention_ += 20;
        cleanliness_ -= 10;
        satiated_ -= 10;
        rested_ -= 20;
        checkBounds();
    }
}

//a method for being able to pet a pet
void Pet::pet() { 
    if (isAlive_) {
        wakeUp();
        attention_ += 10;
        cleanliness_ -= 5;
        satiated_ -= 5;
        rested_ -= 5;
        checkBounds();
    }
}

//method for being able to punch a pet
void Pet::punch(){ 
     if (isAlive_) {
        wakeUp();
        health_ -= 10;
        rested_ -= 10;
        checkBounds();
    } 
}

//method for being able to put your pet to sleep
void Pet::goToSleep() { 
    if (isAlive_) {
        if(rested_ < 100){
            wakeUp();
            rested_ = 100;
            satiated_ -= 20;
            checkBounds();
        }
    } 
}

//method for death of pet
bool Pet::death (){
    if (health_ <= 0 || rested_ <= 0 || satiated_ <= 0) {
            isAlive_ = false;
            return true;
        } else 
         return false;
}

//checking the limits of needs
void Pet::checkBounds() { 
    if (attention_ > MAX_VALUE) attention_ = MAX_VALUE;
    if (attention_ < MIN_VALUE) attention_ = MIN_VALUE;
    if (health_ > MAX_VALUE) health_ = MAX_VALUE;
    if (health_ < MIN_VALUE) health_ = MIN_VALUE;
    if (cleanliness_ > MAX_VALUE) cleanliness_ = MAX_VALUE;
    if (cleanliness_ < MIN_VALUE) cleanliness_ = MIN_VALUE;
    if (rested_ > MAX_VALUE) rested_ = MAX_VALUE;
    if (rested_ < MIN_VALUE) rested_ = MIN_VALUE;
    if (satiated_ > MAX_VALUE) satiated_ = MAX_VALUE;
    if (satiated_ < MIN_VALUE) satiated_ = MIN_VALUE;
}

//checking the pet's mood
void Pet::checkMood(){ 
    double generalMood = ((attention_ *0.8)+ health_ + rested_*0.8 + satiated_ + (cleanliness_*0.5)) / 5;
    if(generalMood >= 60 && generalMood <= 100){
        currentMood_ = MOOD::HAPPY; 
    }else if(generalMood >= 40 && generalMood < 60){//знову змінила діапазон стану
        currentMood_ = MOOD::NORMAL;
    }else{
        currentMood_ = MOOD::SAD;
    }
}

//method to wake up the pet
void Pet::wakeUp(){  
    isAwaken_ = true;
}

//method for rearranging the frame when drawing a pet
void Pet::nextFrame(){ 
    happy_ = happy_ -> next;
    sad_ = sad_ -> next;
    usual_ = usual_ ->next;
    sleep_ = sleep_ -> next;
    death_ = death_ -> next;
}

//a method for drawing a pet depending on its mood
void Pet::drawPet(){  
    if(!isAlive_){
        death_ -> printFrame();
    }else if(!isAwaken_){
        sleep_ -> printFrame();
    }else if(currentMood_ == MOOD::HAPPY){
        happy_ -> printFrame();
    }else if(currentMood_ == MOOD::NORMAL){
        usual_ -> printFrame();
    }else if(currentMood_ == MOOD::SAD){
        sad_ -> printFrame();
    }else{
        usual_ -> printFrame();
    }
}




