// Parser.h - header definition for KaoLang parser class
#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "Command.h"

class Parser {
private:
    std::vector<unsigned char> bytes_;
    std::vector<char32_t> code_points_;
    std::vector<Command> program_;
    std::unordered_map<std::u32string, Command> kaomoji_map_;

    void initKaomojiMap();
    std::string commandToString(Command cmd);
    void bytesToCodePoints();
    void kaomojiToCommands();

public:
    Parser(const std::vector<unsigned char>& bytes);
    const std::vector<Command>& getProgram() const;
};