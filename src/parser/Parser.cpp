// Parser.cpp - implementation of KaoLang parser class
#include "Parser.h"
#include "../utf/utf_utils.h"

Parser::Parser(const std::vector<unsigned char>& bytes) : bytes_(bytes) {
    initKaomojiMap();
    bytesToCodePoints();
    kaomojiToCommands();
}

const std::vector<Command>& Parser::getProgram() const {
    return program_;
}

void Parser::initKaomojiMap() {
    kaomoji_map_ = {
        {U"👈(ﾟヮﾟ👈)", Command::SHIFT_LEFT},
        {U"(👉ﾟヮﾟ)👉", Command::SHIFT_RIGHT},
        {U"👈(⌒▽⌒)👉", Command::NAND},
        {U"(ヘ･_･)ヘ┳━┳", Command::LOOP_START},
        {U"(╯°□°）╯︵ ┻━┻", Command::LOOP_END},
        {U"✍️(◔◡◔)", Command::WRITE},
        {U"(⓿_⓿)", Command::READ},
        {U"o(( >ω<))o", Command::MOVE_RIGHT},
        {U"o((>ω< ))o", Command::MOVE_LEFT},
        {U"ᕦ(ò_óˇ)ᕤ", Command::COPY_TO_REGISTER}
    };
}

std::string Parser::commandToString(Command cmd) {
    switch (cmd) {
        case Command::SHIFT_LEFT: return "SHIFT_LEFT";
        case Command::SHIFT_RIGHT: return "SHIFT_RIGHT";
        case Command::NAND: return "NAND";
        case Command::LOOP_START: return "LOOP_START";
        case Command::LOOP_END: return "LOOP_END";
        case Command::WRITE: return "WRITE";
        case Command::READ: return "READ";
        case Command::MOVE_LEFT: return "MOVE_LEFT";
        case Command::MOVE_RIGHT: return "MOVE_RIGHT";
        case Command::COPY_TO_REGISTER: return "COPY_TO_REGISTER";
        default: return "UNKNOWN_COMMAND";
    }
}

void Parser::bytesToCodePoints() {
    for (int cur_byte_index = 0; cur_byte_index < (int)bytes_.size();) {
        // calc how many bytes this unicode character need
        unsigned int expected_bytes_count = utf8_expected_bytes(bytes_[cur_byte_index]);
        char32_t code_point = utf8_decode(bytes_, cur_byte_index, expected_bytes_count);
        code_points_.push_back(code_point);

        cur_byte_index += expected_bytes_count;
    }
}

void Parser::kaomojiToCommands() {
    size_t i = 0;
    while (i < code_points_.size()) {
        bool matched = false;
        // Try to match each kaomoji
        for (const auto& pair : kaomoji_map_) {
            const std::u32string& kaomoji = pair.first;
            Command cmd = pair.second;

            // Check if the kaomoji matches the current position
            if (i + kaomoji.size() <= code_points_.size()) {
                bool is_match = true;
                for (size_t j = 0; j < kaomoji.size(); ++j) {
                    if (code_points_[i + j] != kaomoji[j]) {
                        is_match = false;
                        break;
                    }
                }
                if (is_match) {
                    program_.push_back(cmd);
                    i += kaomoji.size();
                    matched = true;
                    break;
                }
            }
        }
        if (!matched) {
            // If no kaomoji matched, just move to the next code point
            ++i;
        }
    }
}