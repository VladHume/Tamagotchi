#ifndef FRAMELIST_H
#define FRAMELIST_H

#include <iostream>
#include <vector>
#include <string>

typedef struct Frames Frames;
struct Frames {
    std::vector<std::string> frame;
    Frames* next;

    Frames() : next(nullptr) {}
    ~Frames() {
        frame.clear();
        if (next != nullptr) {
            delete next;
        }
    }

    void printFrame() {
        for (size_t i = 0; i < frame.size(); ++i) {
            std::cout << frame[i] << std::endl;
        }
    }


    // Frames& operator=(const Frames& other) {
    //     if (this == &other) return *this;
        
    //     frame = other.frame;
    //     delete next;
    //     next = other.next ? new Frames(*other.next) : nullptr;
        
    //     return *this;
    // }
};

#endif