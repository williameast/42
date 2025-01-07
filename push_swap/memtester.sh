#!/bin/bash

# Exit immediately if any command fails
set -e

# Colors for output
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
CYAN="\033[0;36m"
NC="\033[0m" # No color

# Check if enough arguments are provided
if [ $# -lt 2 ]; then
    echo -e "Usage: $0 <executable> <test_cases_file>"
    exit 1
fi

# Command-line arguments
EXECUTABLE="$1"
TEST_CASES_FILE="$2"

# Check if the executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Executable '${EXECUTABLE}' not found.${NC}"
    exit 1
fi

# Check if the test cases file exists
if [ ! -f "$TEST_CASES_FILE" ]; then
    echo -e "${RED}Error: Test cases file '${TEST_CASES_FILE}' not found.${NC}"
    exit 1
fi

# Function to run a single test with valgrind
run_valgrind_test() {
    local test_input="$1"
    echo -e "${CYAN}Running test with input: ${test_input}${NC}"

    # Run valgrind and capture the output
    output=$(valgrind --leak-check=full --error-exitcode=1 $EXECUTABLE $test_input 2>&1)
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Test passed: No memory leaks detected for input: ${test_input}${NC}"
    else
        echo -e "${RED}Test failed: Memory leaks detected for input: ${test_input}${NC}"
        echo -e "${YELLOW}Valgrind Output:${NC}"
        echo "$output" # Show the valgrind output on failure
        exit 1
    fi
}

# Read test cases from the file and run them
while IFS= read -r test_input || [ -n "$test_input" ]; do
    run_valgrind_test "$test_input"
done < "$TEST_CASES_FILE"

echo -e "${GREEN}All tests passed: No memory leaks detected.${NC}"
