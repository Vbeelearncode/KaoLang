// Interpreter.cpp - implementation of KaoLang interpreter

#include "Interpreter.h"

#include <iostream>
#include <istream>

Interpreter::Interpreter(std::istream& input_stream) 
: counter_(0), register_(0), tape_(), input_stream_(input_stream) {
    initCommandMap();
}

Interpreter::Interpreter(std::istream& input_stream, const std::vector<std::string>& program)
    : counter_(0), register_(0), program_(program), tape_(), input_stream_(input_stream) {
    initCommandMap();
}

void Interpreter::loadProgram(const std::vector<std::string>& program) {
    program_ = program;
    counter_ = 0;
    register_ = 0;
    stack_.clear();
    tape_ = Tape();
}

void Interpreter::initCommandMap() {
    command_map_ = {
        {"SHIFT_LEFT", [this]() { shiftLeftMemoryCell(); }},
        {"SHIFT_RIGHT", [this]() { shiftRightMemoryCell(); }},
        {"NAND", [this]() { applyNANDToMemoryCell(); }},
        {"LOOP_START", [this]() { loopStart(); }},
        {"LOOP_END", [this]() { loopEnd(); }},
        {"WRITE", [this]() { writeCharFromMemoryCell(); }},
        {"READ", [this]() { readNextByte(); }},
        {"MOVE_LEFT", [this]() { moveLeftOnTape(); }},
        {"MOVE_RIGHT", [this]() { moveRightOnTape(); }},
        {"COPY_TO_REGISTER", [this]() { copyMemoryCellToRegister(); }}
    };
}

void Interpreter::runNextCommand() {
    if (counter_ >= program_.size()) {
        return;
    }

    const std::string& command = program_[counter_];
    auto it = command_map_.find(command);
    if (it != command_map_.end()) {
        it->second();
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
    }

    ++counter_;
}

void Interpreter::runAll() {
    while (counter_ < program_.size()) {
        runNextCommand();
    }
}

void Interpreter::shiftLeftMemoryCell() {
    tape_.valueShiftLeft();
}

void Interpreter::shiftRightMemoryCell() {
    tape_.valueShiftRight();
}

void Interpreter::applyNANDToMemoryCell() {
    tape_.nandCurrentCellValue(register_);
    register_ = 0;
}

void Interpreter::loopStart() {
    if (tape_.getCurrentCellValue() == 0) {
        int loop_counter = 1;
        while (loop_counter > 0 && ++counter_ < program_.size()) {
            if (program_[counter_] == "LOOP_START") {
                ++loop_counter;
            } else if (program_[counter_] == "LOOP_END") {
                --loop_counter;
            }
        }
    } else {
        stack_.push_back(counter_);
    }
}

void Interpreter::loopEnd() {
    if (!stack_.empty()) {
        if (tape_.getCurrentCellValue() != 0) {
            counter_ = stack_.back() - 1;
        }
        stack_.pop_back();
    }
}

void Interpreter::writeCharFromMemoryCell() {
    char output_char = (char)(tape_.getCurrentCellValue() & 0xFF);
    std::cout << output_char;
}

void Interpreter::moveLeftOnTape() {
    tape_.moveLeft();
}

void Interpreter::moveRightOnTape() {
    tape_.moveRight();
}

void Interpreter::copyMemoryCellToRegister() {
    register_ = tape_.getCurrentCellValue();
}

void Interpreter::readNextByte() {
    char input_char;
    if (input_stream_.get(input_char)) {
        tape_.setCurrentCellValue(static_cast<int>(input_char));
    } else {
        tape_.setCurrentCellValue(0);
    }
}