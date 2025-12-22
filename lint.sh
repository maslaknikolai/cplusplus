#!/bin/bash

# C++ Linting and Formatting Script
# Usage: ./lint.sh [format|check|all]

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CLANG_TIDY="/opt/homebrew/opt/llvm/bin/clang-tidy"
CLANG_FORMAT="/opt/homebrew/opt/llvm/bin/clang-format"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

function show_usage() {
    echo "Usage: $0 [format|check|all]"
    echo "  format  - Format all C++ files using clang-format"
    echo "  check   - Run clang-tidy linting checks"
    echo "  all     - Run both formatting and linting (default)"
}

function run_format() {
    echo -e "${GREEN}Running clang-format...${NC}"
    find "$SCRIPT_DIR" -name "*.cpp" -o -name "*.h" -o -name "*.hpp" | while read file; do
        echo "Formatting: $file"
        "$CLANG_FORMAT" -i "$file"
    done
    echo -e "${GREEN}Formatting complete!${NC}"
}

function run_lint() {
    echo -e "${GREEN}Running clang-tidy...${NC}"
    
    # Check if build directory exists
    if [ ! -d "$SCRIPT_DIR/build" ]; then
        echo -e "${YELLOW}Build directory not found. Creating and running cmake...${NC}"
        mkdir -p "$SCRIPT_DIR/build"
        cd "$SCRIPT_DIR/build" && cmake ..
    fi
    
    # Run linting via CMake target if available, otherwise run manually
    if [ -f "$SCRIPT_DIR/build/Makefile" ]; then
        make -C "$SCRIPT_DIR/build" lint
    else
        echo -e "${YELLOW}Running clang-tidy manually...${NC}"
        "$CLANG_TIDY" --config-file="$SCRIPT_DIR/.clang-tidy" \
                      --header-filter=.* \
                      "$SCRIPT_DIR/main.cpp" \
                      -- -std=c++17 -I"$SCRIPT_DIR/include"
    fi
}

function run_all() {
    run_format
    echo ""
    run_lint
}

# Check if required tools are available
if [ ! -f "$CLANG_TIDY" ]; then
    echo -e "${RED}Error: clang-tidy not found at $CLANG_TIDY${NC}"
    echo "Install with: brew install llvm"
    exit 1
fi

if [ ! -f "$CLANG_FORMAT" ]; then
    echo -e "${RED}Error: clang-format not found at $CLANG_FORMAT${NC}"
    echo "Install with: brew install llvm"
    exit 1
fi

# Parse command line arguments
case "${1:-all}" in
    format)
        run_format
        ;;
    check)
        run_lint
        ;;
    all)
        run_all
        ;;
    *)
        show_usage
        exit 1
        ;;
esac