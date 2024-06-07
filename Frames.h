#ifndef FRAMELIST_H
#define FRAMELIST_H

#include <iostream>
#include <vector>
#include <string>

typedef struct Frames Frames;

// Definition of the Frames struct
struct Frames {
    std::vector<std::string> frame; // A vector to store strings representing the frame data
    Frames* next; // Pointer to the next Frames object in the linked list

    // Constructor: Initializes the 'next' pointer to nullptr
    Frames() : next(nullptr) {}

    // Destructor: Clears the frame vector and recursively deletes the next Frames object
    ~Frames() {
        frame.clear(); // Clear the vector to release its memory
        if (next != nullptr) { // Check if there is a next Frames object
            delete next; // Delete the next Frames object, which will call its destructor
        }
    }

    // Method to print all strings in the frame vector to the standard output
    void printFrame() {
        for (size_t i = 0; i < frame.size(); ++i) { // Loop through each string in the frame vector
            std::cout << frame[i] << std::endl; // Print the current string
        }
    }
};


#endif