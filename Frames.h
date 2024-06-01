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
};

#endif