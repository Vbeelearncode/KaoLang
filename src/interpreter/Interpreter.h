// Interpreter.h - interface for KaoLang interpreter
#pragma once

#include <istream>
#include <vector>
#include <string>
#include <Tape.h>

class Interpreter {
private:
    int counter_;
    int register_;
    std::vector<int> stack_;
    std::vector<std::string> program_;
    std::istream& input_stream_;
    Tape tape_;
    std::unordered_map<std::string, std::function<void()>> command_map_;

    void initCommandMap();
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

public:
    Interpreter(std::istream& input_stream);
    Interpreter(std::istream& input_stream, const std::vector<std::string>& program);
    void loadProgram(const std::vector<std::string>& program);
    void runNextCommand();
    void runAll();
};