// Tape.cpp - implementation of the Tape class
#include "Tape.h"

Tape::Tape() : cur_index_(0), cells_(1, 0) {}

int Tape::getCurrentCellValue() const {
    return cells_[cur_index_];
}

void Tape::nandCurrentCellValue(int value) {
    cells_[cur_index_] = ~(cells_[cur_index_] & value);
}

void Tape::setCurrentCellValue(int value) {
    cells_[cur_index_] = value;
}

void Tape::valueShiftLeft() {
    cells_[cur_index_] <<= 1;
}

void Tape::valueShiftRight() {
    cells_[cur_index_] >>= 1;
}

void Tape::moveLeft() {
    if (cur_index_ == 0) {
        cells_.push_back(0);
        cur_index_ = cells_.size() - 1;
    } else {
        --cur_index_;
    }
}

void Tape::moveRight() {
    ++cur_index_;
    if (cur_index_ >= cells_.size()) {
        cells_.push_back(0);
    }
}