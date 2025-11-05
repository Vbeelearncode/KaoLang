#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

#include "utf/utf_utils.h"
#include "interpreter/Interpreter.h"
#include "parser/Parser.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1; // Emscripten will automatically call main when page loads, so I'll not run the program if < 2 arguments are provided
    }
    // get program file from argument
    std::ifstream file(argv[1], std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    // get input stream from argument or use stdin if no argument is provided
    std::istream* input_stream = nullptr;
    std::ifstream filestream;
    
    if (argc < 3) {
        input_stream = &std::cin;
    } else {
        filestream.open(argv[2], std::ios::binary);
        if (!filestream.is_open()) {
            std::cerr << "Failed to open file: " << argv[2] << std::endl;
            return 1;
        }
        input_stream = &filestream;
    }

    // get output stream from argument or use stdout if no argument is provided
    std::ostream* output_stream = nullptr;
    std::ofstream outfilestream;
    if (argc < 4) {
        output_stream = &std::cout;
    } else {
        outfilestream.open(argv[3], std::ios::app | std::ios::binary);
        if (!outfilestream.is_open()) {
            std::cerr << "Failed to open file: " << argv[3] << std::endl;
            return 1;
        }
        output_stream = &outfilestream;
    }

    // pass file begin iterator and null iterator to vector constructor
    // it will copy every byte in between into the vector
    std::vector<unsigned char> bytes{
        std::istreambuf_iterator<char>(file),
        std::istreambuf_iterator<char>()
    };

    // match code points with Kaomoji to produce program vector with human/program readable instructions
    Parser parser = Parser(bytes);
    const std::vector<Command> program = parser.getProgram();
    
    Interpreter interpreter(*input_stream, *output_stream, program);
    interpreter.runAll();
    return 0;
}