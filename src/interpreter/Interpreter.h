// Interpreter.h - interface for KaoLang interpreter
#pragma once

#include <istream>
#include <vector>
#include <string>
#include <optional>
#include "Tape.h"
#include "Command.h"

class Interpreter {
private:
    int counter_;
    std::optional<int> reg_;
    std::vector<int> stack_;
    std::vector<Command> program_;
    std::istream& input_stream_;
    std::ostream& output_stream_;
    Tape tape_;

    void shiftLeftMemoryCell();
    void shiftRightMemoryCell();
    void applyNANDToMemoryCell();
    void loopStart();
    void loopEnd();
    void writeCharFromMemoryCell();
    void moveLeftOnTape();
    void moveRightOnTape();
    void copyMemoryCellToRegister();
    void readNextByte();
    void printStatus(); // for debugging

public:
    Interpreter(std::istream& input_stream, std::ostream& output_stream);
    Interpreter(std::istream& input_stream, std::ostream& output_stream, const std::vector<Command>& program);
    void loadProgram(const std::vector<Command>& program);
    void runNextCommand();
    void runAll();
};