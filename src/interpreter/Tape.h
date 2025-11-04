// Tape.h - psedo infinite type to represent memory
#pragma once

#include <vector>

class Tape {
private:
    int cur_index_;
    std::vector<int> cells_;

public:
    Tape();
    int getCurrentCellValue() const;
    void setCurrentCellValue(int value);
    void valueShiftLeft();
    void valueShiftRight();
    void moveLeft();
    void moveRight();
};