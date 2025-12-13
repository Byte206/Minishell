#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0
TOTAL=0

# Function to run a test
run_test() {
    local test_num=$1
    local description=$2
    local command=$3
    local expected=$4
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}Test $test_num:${NC} $description"
    
    # Execute command
    eval "$command" > /tmp/minishell_test_output.txt 2>&1
    local exit_code=$?
    
    # Check result
    if [ -n "$expected" ]; then
        if grep -q "$expected" /tmp/minishell_test_output.txt 2>/dev/null || [ "$expected" == "exit_code_0" ] && [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ PASSED${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Expected: $expected"
            echo "Got:"
            cat /tmp/minishell_test_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    else
        echo -e "${YELLOW}⚠ INFO${NC}"
        echo "Output:"
        cat /tmp/minishell_test_output.txt
        echo ""
        PASSED=$((PASSED + 1))
    fi
    
    # Cleanup
    rm -f /tmp/minishell_test_output.txt
}

# Function to cleanup test files
cleanup() {
    rm -f a.txt b.txt c.txt d.txt e.txt
    rm -f file.txt input.txt output.txt temp.txt final.txt
    rm -f nuevo.txt archivo.txt append.txt out.txt
    rm -f pwd_out.txt env_out.txt export_out.txt cd_out.txt unset_out.txt
    rm -f first.txt second.txt empty.txt append_empty.txt
    rm -f salida.txt file_with_spaces.txt "file@#$.txt"
    rm -f .hidden readonly.txt noread.txt log.txt
    rm -rf dir testdir 2>/dev/null
}

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}  Minishell Redirection Tests${NC}"
echo -e "${YELLOW}========================================${NC}\n"

# Setup
cleanup

echo -e "${BLUE}=== BASIC REDIRECTIONS ===${NC}\n"

# Test 1: Create file if not exists
run_test 1 "Create file with >" \
    "echo 'test' > nuevo.txt && cat nuevo.txt" \
    "test"

# Test 2: Truncate existing file
run_test 2 "Truncate with >" \
    "echo 'primero' > archivo.txt && echo 'segundo' > archivo.txt && cat archivo.txt" \
    "segundo"

# Test 3: Append creates file if not exists
run_test 3 "Create with >>" \
    "echo 'nuevo' >> append.txt && cat append.txt" \
    "nuevo"

# Test 4: Append doesn't truncate
run_test 4 "Append with >>" \
    "echo 'linea1' > file.txt && echo 'linea2' >> file.txt && echo 'linea3' >> file.txt && cat file.txt" \
    "linea1"

# Test 5: Input redirection
run_test 5 "Input redirection <" \
    "echo 'contenido' > input.txt && cat < input.txt" \
    "contenido"

echo -e "${BLUE}=== REDIRECTIONS WITH BUILTINS ===${NC}\n"

# Test 7: echo with >
run_test 7 "echo with >" \
    "echo 'salida' > out.txt && cat out.txt" \
    "salida"

# Test 8: pwd with >
run_test 8 "pwd with >" \
    "pwd > pwd_out.txt && test -s pwd_out.txt && echo 'OK'" \
    "OK"

# Test 9: env with >
run_test 9 "env with >" \
    "env > env_out.txt && grep PATH env_out.txt && echo 'OK'" \
    "PATH"

echo -e "${BLUE}=== REDIRECTION ORDER ===${NC}\n"

# Test 13: > before command
run_test 13 "> before command" \
    "> salida.txt echo 'test' && cat salida.txt" \
    "test"

# Test 14: > in middle of arguments
run_test 14 "> in middle of args" \
    "echo > salida.txt 'test' && cat salida.txt" \
    "test"

# Test 16: < before command
run_test 16 "< before command" \
    "echo 'input' > input.txt && < input.txt cat" \
    "input"

# Test 18: Mix < and >
run_test 18 "Mix < and >" \
    "echo 'test' > input.txt && < input.txt cat > output.txt && cat output.txt" \
    "test"

echo -e "${BLUE}=== MULTIPLE REDIRECTIONS ===${NC}\n"

# Test 19: Two > (last prevails)
run_test 19 "Multiple > (last wins)" \
    "echo 'test' > first.txt > second.txt && cat second.txt" \
    "test"

# Test 20: Three > consecutive
run_test 20 "Three > consecutive" \
    "echo 'data' > a.txt > b.txt > c.txt && cat c.txt" \
    "data"

# Test 22: Two >> consecutive
run_test 22 "Two >> consecutive" \
    "echo '1' >> file.txt && echo '2' >> file.txt && cat file.txt" \
    "1"

# Test 23: Mix > and >>
run_test 23 "Mix > and >>" \
    "echo 'a' > file.txt && echo 'b' >> file.txt && echo 'c' > file.txt && echo 'd' >> file.txt && cat file.txt" \
    "c"

echo -e "${BLUE}=== REDIRECTIONS WITH PIPES ===${NC}\n"

# Test 24: Pipe and > at end
run_test 24 "Pipe and > at end" \
    "echo 'test' | cat > output.txt && cat output.txt" \
    "test"

# Test 25: Pipe and < at start
run_test 25 "Pipe and < at start" \
    "echo 'test' > input.txt && cat < input.txt | cat" \
    "test"

# Test 27: Multiple pipes and >
run_test 27 "Multiple pipes and >" \
    "echo 'test' | cat | cat | cat > final.txt && cat final.txt" \
    "test"

# Test 29: Pipe with >>
run_test 29 "Pipe with >>" \
    "echo 'first' > file.txt && echo 'second' | cat >> file.txt && cat file.txt" \
    "first"

echo -e "${BLUE}=== SPECIAL FILENAMES ===${NC}\n"

# Test 34: Relative path
run_test 34 "Relative path" \
    "mkdir -p dir && echo 'test' > dir/file.txt && cat dir/file.txt" \
    "test"

# Test 36: Multiple extensions
run_test 36 "Multiple extensions" \
    "echo 'test' > file.tar.gz && cat file.tar.gz" \
    "test"

echo -e "${BLUE}=== REDIRECTIONS ONLY (NO COMMAND) ===${NC}\n"

# Test 37: Only >
run_test 37 "Only >" \
    "> empty.txt && test -f empty.txt && echo 'OK'" \
    "OK"

# Test 39: Only < (no command)
run_test 39 "Only <" \
    "echo 'test' > input.txt && < input.txt && echo 'OK'" \
    "OK"

# Test 40: Multiple > without command
run_test 40 "Multiple > no command" \
    "> a.txt > b.txt > c.txt && test -f a.txt && test -f b.txt && test -f c.txt && echo 'OK'" \
    "OK"

# Test 41: < and > without command
run_test 41 "< and > no command" \
    "echo 'test' > input.txt && < input.txt > output.txt && cat output.txt" \
    "test"

echo -e "${BLUE}=== ERROR CASES ===${NC}\n"

# Test 42: Redirect to directory
run_test 42 "Redirect to directory (should fail)" \
    "mkdir -p testdir && echo 'test' > testdir 2>&1 | grep -i 'directory' && echo 'ERROR_OK'" \
    "ERROR_OK"

# Test 46: Redirect to /dev/null
run_test 46 "Redirect to /dev/null" \
    "echo 'desaparece' > /dev/null && echo 'OK'" \
    "OK"

# Test 47: Read from /dev/null
run_test 47 "Read from /dev/null" \
    "cat < /dev/null && echo 'OK'" \
    "OK"

echo -e "${BLUE}=== REDIRECTIONS WITH VARIABLES ===${NC}\n"

# Test 48: Filename from variable
run_test 48 "Filename from variable" \
    "export FILE=output.txt && echo 'test' > \$FILE && cat \$FILE" \
    "test"

echo -e "${BLUE}=== EXIT CODES ===${NC}\n"

# Test 52: Exit code after successful redirection
run_test 52 "Exit code after success" \
    "echo 'test' > file.txt && [ \$? -eq 0 ] && echo 'OK'" \
    "OK"

# Test 53: Exit code after failed redirection
run_test 53 "Exit code after failure" \
    "echo 'test' > /no/existe/dir/file.txt 2>/dev/null; [ \$? -ne 0 ] && echo 'ERROR_OK'" \
    "ERROR_OK"

# Cleanup
cleanup

# Summary
echo -e "\n${YELLOW}========================================${NC}"
echo -e "${YELLOW}  Test Summary${NC}"
echo -e "${YELLOW}========================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "${YELLOW}========================================${NC}\n"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed! 🎉${NC}\n"
    exit 0
else
    echo -e "${RED}Some tests failed 😞${NC}\n"
    exit 1
fi
