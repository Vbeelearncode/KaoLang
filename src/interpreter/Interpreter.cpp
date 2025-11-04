// Interpreter.cpp - implementation of KaoLang interpreter

#include "Interpreter.h"

#include <iostream>
#include <istream>
#include <cctype>

Interpreter::Interpreter(std::istream& input_stream) 
: counter_(0), tape_(), input_stream_(input_stream) {}

Interpreter::Interpreter(std::istream& input_stream, const std::vector<Command>& program)
    : counter_(0), program_(program), tape_(), input_stream_(input_stream) {}

void Interpreter::loadProgram(const std::vector<Command>& program) {
    program_ = program;
    counter_ = 0;
    reg_ = std::nullopt;
    stack_.clear();
    tape_ = Tape();
}

void Interpreter::runNextCommand() {
    if (counter_ >= program_.size()) {
        return;
    }

    Command cmd = program_[counter_];

    switch (cmd) {
        case Command::SHIFT_LEFT: shiftLeftMemoryCell(); break;
        case Command::SHIFT_RIGHT: shiftRightMemoryCell(); break;
        case Command::NAND: applyNANDToMemoryCell(); break;
        case Command::LOOP_START: loopStart(); break;
        case Command::LOOP_END: loopEnd(); break;
        case Command::WRITE: writeCharFromMemoryCell(); break;
        case Command::READ: readNextByte(); break;
        case Command::MOVE_LEFT: moveLeftOnTape(); break;
        case Command::MOVE_RIGHT: moveRightOnTape(); break;
        case Command::COPY_TO_REGISTER: copyMemoryCellToRegister(); break;
        default: break;
    }

    ++counter_;
    // printStatus(); // for debugging
}

void Interpreter::runAll() {
    while (counter_ < program_.size()) {
        runNextCommand();
    }
}

void Interpreter::printStatus() {
    std::cout << "Counter: " << counter_ << ", Register: " << (reg_.has_value() ? std::to_string(reg_.value()) : "None") << std::endl;
    std::cout << "Stack: ";
    for (int addr : stack_) {
        std::cout << addr << " ";
    }
    std::cout << std::endl;
    tape_.printStatus();
}

void Interpreter::shiftLeftMemoryCell() {
    tape_.valueShiftLeft();
}

void Interpreter::shiftRightMemoryCell() {
    tape_.valueShiftRight();
}

void Interpreter::applyNANDToMemoryCell() {
    if (reg_.has_value()) {
        tape_.nandCurrentCellValue(reg_.value());
        reg_.reset();
    } else {
        tape_.nandCurrentCellValue(0);
    }
}

void Interpreter::loopStart() {
    if (tape_.getCurrentCellValue() == 0) {
        int loop_counter = 1;
        while (loop_counter > 0 && ++counter_ < program_.size()) {
            if (program_[counter_] == Command::LOOP_START) {
                ++loop_counter;
            } else if (program_[counter_] == Command::LOOP_END) {
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
    if (reg_.has_value()) {
        tape_.setCurrentCellValue(reg_.value());
        reg_.reset();
    } else {
        reg_ = tape_.getCurrentCellValue();
    }
}

void Interpreter::readNextByte() {
    char input_char;
    
    // skip whitespace
    do {
        if (!input_stream_.get(input_char)) {
            // set memory cell value to 0 if there's nothing in input stream
            tape_.setCurrentCellValue(0);
            return;
        }
    } while (std::isspace(static_cast<unsigned char>(input_char)));
    
    tape_.setCurrentCellValue(static_cast<int>(input_char));
}