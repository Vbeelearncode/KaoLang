// Interpreter.h - interface for KaoLang interpreter
#pragma once

#include <vector>
#include <string>
#include <Tape.h>

class Interpreter {
private:
    int p_counter;
    int p_register;
    std::vector<int> p_stack;
    std::vector<std::string> p_program;
    Tape p_tape;

    void shiftLeftMemoryCell();
    void shiftRightMemoryCell();
    void applyNANDToMemoryCell();
    void loopStart();
    void loopEnd();
    void writeCharFromMemoryCell();
    void readCharToMemoryCell(char input_char);
    void moveLeftOnTape();
    void moveRightOnTape();
    void copyMemoryCellToRegister();

public:
    Interpreter();
    Interpreter(const std::vector<std::string>& program);
    void loadProgram(const std::vector<std::string>& program);
    void run();
};