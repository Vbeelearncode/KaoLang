cmake_minimum_required(VERSION 3.23)

project(KaoLang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(KaoLang src/main.cpp)

set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter/Interpreter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter/Tape.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utf/utf_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/Parser.cpp
)

target_sources(KaoLang
    PRIVATE
    ${SRC_FILES}
)

target_include_directories(KaoLang
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utf
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser
)