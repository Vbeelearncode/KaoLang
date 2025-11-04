// Tape.h - psedo infinite type to represent memory
#pragma once

#include <vector>

class Tape {
private:
    int cur_index_;
    std::vector<uint8_t> cells_;

public:
    Tape();
    uint8_t getCurrentCellValue() const;
    void nandCurrentCellValue(uint8_t value);
    void setCurrentCellValue(uint8_t value);
    void valueShiftLeft();
    void valueShiftRight();
    void moveLeft();
    void moveRight();
    void printStatus() const; // for debugging
};