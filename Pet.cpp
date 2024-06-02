#include "Pet.h"
#include "Player.h"
#include "FileUtility.h"
#include <iostream>
#include <cstring>
#include <string>

//змінила орядок оголошення в конструкторі
Pet::Pet(std::string name, Frames *happy, Frames *sad, Frames *usual, Frames *sleep, Frames *death): name_(name), attention_(60), health_(100), cleanliness_(60), rested_(90), satiated_(60) , isAlive_(true), currentMood_(MOOD::NORMAL), isAwaken_(true), happy_(happy), sad_(sad), usual_(usual), sleep_(sleep), death_(death){}

Pet::Pet(): name_(""), attention_(0), health_(0), cleanliness_(0), rested_(0), satiated_(0), 
isAlive_(true), currentMood_(MOOD::NORMAL), isAwaken_(true),  happy_(nullptr), sad_(nullptr),
usual_(nullptr), sleep_(nullptr), death_(nullptr) {}

Pet::~Pet() //додала віртуальний деструктор щоб прибрати попередження
{
}

//гетери
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

//метод який повертає стрінгове знчення настрою пета
std::string Pet::getStringMood() {
    switch(currentMood_) {
        case MOOD::HAPPY:
            return "HAPPY";
        case MOOD::NORMAL:
            return "NORMAL";
        case MOOD::SAD:
            return "SAD";
        default:
            return " ";
    }
}

//сетери
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


void Pet::feed() { //погодувати
     if (isAlive_) {
        satiated_ += 20;
        cleanliness_ -= 10;
        rested_ -= 10;
        health_ += 5;
        checkBounds();
     }
}

   
void Pet::treat(){ //лікувати
      if (isAlive_) {
        if(health_ < 90){
            health_ = 100;
            rested_ -= 10;
            checkBounds();
        }
    }
}


void Pet::clean() { //почистити 
     if (isAlive_) {
        cleanliness_ += 30;
        rested_ -= 10;
        checkBounds();
    }
}


void Pet::play(){ //пограти
    if (isAlive_) {
        attention_ += 20;
        cleanliness_ -= 10;
        satiated_ -= 10;
        rested_ -= 20;
        checkBounds();
    }
}


void Pet::pet() { //погладити
    if (isAlive_) {
        attention_ += 10;
        cleanliness_ -= 5;
        satiated_ -= 5;
        rested_ -= 5;
        checkBounds();
    }
}


void Pet::punch(){ //вдарити :(
     if (isAlive_) {
        health_ -= 10;
        rested_ -= 10;
        checkBounds();
    } 
}


void Pet::goToSleep() { //покласти спати
    if (isAlive_) {
        if(rested_ < 100){
            isAwaken_ = false;
            rested_ = 100;
            satiated_ -= 20;
            checkBounds();
        }
    } 
}

void Pet::checkBounds() { //перевірка меж потреб
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


void Pet::checkMood(){ //перевірка настрою
    double generalMood = ((attention_ *0.8)+ health_ + rested_*0.8 + satiated_ + (cleanliness_*0.5)) / 5;
    if(generalMood >= 70 && generalMood <= 100){
        currentMood_ = MOOD::HAPPY;
    }else if(generalMood >= 30 && generalMood < 70){
        currentMood_ = MOOD::NORMAL;
    }else{
        currentMood_ = MOOD::SAD;
    }
}

void Pet::wakeUp(){  //розбудити
    isAwaken_ = true;
}

void Pet::nextFrame(){ //перестановка кадру
    happy_ = happy_ -> next;
    sad_ = sad_ -> next;
    usual_ = usual_ ->next;
    sleep_ = sleep_ -> next;
    death_ = death_ -> next;
}

void Pet::drawPet(){  //відмалювати пета по настрою або стану
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




