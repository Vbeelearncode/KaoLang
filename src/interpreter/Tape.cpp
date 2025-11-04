// Tape.cpp - implementation of the Tape class
#include "Tape.h"
#include <iostream>

Tape::Tape() : cur_index_(0), cells_(1, 0) {}

uint8_t Tape::getCurrentCellValue() const {
    return cells_[cur_index_];
}

void Tape::nandCurrentCellValue(uint8_t value) {
    cells_[cur_index_] = ~(cells_[cur_index_] & value);
}

void Tape::setCurrentCellValue(uint8_t value) {
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

void Tape::printStatus() const {
    std::cout << "Tape Status: [";
    for (size_t i = 0; i < cells_.size(); ++i) {
        if (i == cur_index_) {
            std::cout << "(" << static_cast<int>(cells_[i]) << ") ";
        } else {
            std::cout << static_cast<int>(cells_[i]) << " ";
        }
    }
    std::cout << "]" << std::endl;
}