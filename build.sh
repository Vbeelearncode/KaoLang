#!/bin/bash
# build.sh: compile KaoLang to WebAssembly using em++.

# Output paths
OUT_DIR="docs"
OUT_JS="$OUT_DIR/kaolang.js"

# Make sure output directory exists
mkdir -p "$OUT_DIR"

# Compile with em++
em++ \
  src/main.cpp \
  src/interpreter/Interpreter.cpp \
  src/interpreter/Tape.cpp \
  src/utf/utf_utils.cpp \
  src/parser/Parser.cpp \
  -I src/interpreter \
  -I src/utf \
  -I src/parser \
  -O3 \
  -s WASM=1 \
  -s MODULARIZE=1 \
  -s EXPORT_ES6=1 \
  -s ENVIRONMENT=web \
  -s EXPORT_NAME=createKaoLang \
  -s EXPORTED_FUNCTIONS='["_main"]' \
  -s EXPORTED_RUNTIME_METHODS='["FS","callMain","ccall","cwrap"]' \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s NO_EXIT_RUNTIME=1 \
  -o "$OUT_JS"

echo "Build finished! Output: $OUT_JS"
