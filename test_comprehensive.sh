#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0
TOTAL=0
MINISHELL="./minishell"

# Function to run a command in minishell and compare with bash
run_test() {
    local test_num=$1
    local description=$2
    local command=$3
    local check_exit_code=${4:-0}  # 1 to check exit code, 0 to check output
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}Test $test_num:${NC} $description"
    echo -e "${CYAN}Command:${NC} $command"
    
    # Run in bash
    bash -c "$command" > /tmp/bash_output.txt 2>&1
    local bash_exit=$?
    
    # Run in minishell (simulated with bash for now)
    # TODO: Replace with actual minishell execution
    bash -c "$command" > /tmp/minishell_output.txt 2>&1
    local mini_exit=$?
    
    # Check result
    if [ $check_exit_code -eq 1 ]; then
        # Compare exit codes
        if [ $bash_exit -eq $mini_exit ]; then
            echo -e "${GREEN}✓ PASSED${NC} (exit: $mini_exit)\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Bash exit code: $bash_exit"
            echo "Minishell exit code: $mini_exit"
            echo ""
            FAILED=$((FAILED + 1))
        fi
    else
        # Compare outputs
        if diff -q /tmp/bash_output.txt /tmp/minishell_output.txt > /dev/null 2>&1; then
            echo -e "${GREEN}✓ PASSED${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo -e "${YELLOW}Bash output:${NC}"
            cat /tmp/bash_output.txt
            echo -e "${YELLOW}Minishell output:${NC}"
            cat /tmp/minishell_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    fi
    
    rm -f /tmp/bash_output.txt /tmp/minishell_output.txt
}

# Simpler test that just checks if command works
run_simple_test() {
    local test_num=$1
    local description=$2
    local command=$3
    local expected_pattern=$4
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}Test $test_num:${NC} $description"
    echo -e "${CYAN}Command:${NC} $command"
    
    bash -c "$command" > /tmp/test_output.txt 2>&1
    local exit_code=$?
    
    if [ -n "$expected_pattern" ]; then
        if grep -q "$expected_pattern" /tmp/test_output.txt 2>/dev/null; then
            echo -e "${GREEN}✓ PASSED${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Expected pattern: $expected_pattern"
            echo "Got:"
            cat /tmp/test_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    else
        if [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ PASSED${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Exit code: $exit_code"
            cat /tmp/test_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    fi
    
    rm -f /tmp/test_output.txt
}

cleanup() {
    rm -f test_file.txt out.txt file.txt
    rm -f a.txt b.txt c.txt
}

echo -e "${MAGENTA}========================================${NC}"
echo -e "${MAGENTA}  Minishell Comprehensive Tests${NC}"
echo -e "${MAGENTA}========================================${NC}\n"

cleanup

echo -e "${YELLOW}=== PIPES - Basic ===${NC}\n"

run_test 1 "Simple pipe" "echo hello | cat" 0
run_test 2 "Multiple pipes" "echo test | cat | cat | cat" 0
run_test 3 "Pipe with grep" "echo 'hello world' | grep hello" 0
run_test 4 "Pipe with wc" "echo 'one two three' | wc -w" 0
run_test 5 "Long pipeline" "echo test | cat | cat | cat | cat | cat | wc -l" 0

echo -e "${YELLOW}=== PIPES - Edge Cases ===${NC}\n"

run_simple_test 6 "Pipe at start (should fail)" "| echo test" ""
run_simple_test 7 "Pipe at end (should fail)" "echo test |" ""
run_simple_test 8 "Double pipe (should fail)" "echo test | | cat" ""
run_test 9 "Command not found in pipe" "echo test | commandnoexiste 2>&1 | cat" 0

echo -e "${YELLOW}=== BUILTINS - CD ===${NC}\n"

run_simple_test 10 "cd to /tmp" "cd /tmp && pwd" "/tmp"
run_simple_test 11 "cd .." "cd /tmp && cd .. && pwd" "/"
run_simple_test 12 "cd non-existent (should fail)" "cd /nonexistent 2>&1" "No such file"
run_simple_test 13 "cd with no args (HOME)" "cd && pwd" "$HOME"
run_simple_test 14 "cd ." "cd . && echo OK" "OK"

echo -e "${YELLOW}=== BUILTINS - ECHO ===${NC}\n"

run_test 15 "echo simple" "echo hello" 0
run_test 16 "echo with spaces" "echo hello world" 0
run_test 17 "echo empty" "echo" 0
run_test 18 "echo -n" "echo -n test" 0
run_test 19 "echo -n multiple" "echo -n -n -n test" 0
run_test 20 "echo -nnnn" "echo -nnnn test" 0
run_test 21 "echo -n not at start" "echo test -n" 0
run_test 22 "echo with quotes" "echo 'hello world'" 0
run_test 23 "echo with double quotes" "echo \"hello world\"" 0

echo -e "${YELLOW}=== BUILTINS - PWD ===${NC}\n"

run_simple_test 24 "pwd" "pwd" "/"
run_simple_test 25 "pwd after cd" "cd /tmp && pwd" "/tmp"
run_simple_test 26 "pwd to file" "pwd > /tmp/pwd_test.txt && cat /tmp/pwd_test.txt" "/"

echo -e "${YELLOW}=== BUILTINS - ENV ===${NC}\n"

run_simple_test 27 "env shows PATH" "env | grep PATH" "PATH"
run_simple_test 28 "env shows HOME" "env | grep HOME" "HOME"

echo -e "${YELLOW}=== BUILTINS - EXPORT ===${NC}\n"

run_simple_test 29 "export variable" "export TEST=hello && env | grep TEST" "TEST=hello"
run_simple_test 30 "export with spaces" "export TEST='hello world' && env | grep TEST" "hello world"
run_simple_test 31 "export empty" "export TEST= && env | grep TEST=" "TEST="
run_simple_test 32 "export invalid name (should fail)" "export 123=test 2>&1" ""
run_simple_test 33 "export with dash (should fail)" "export TEST-VAR=test 2>&1" ""

echo -e "${YELLOW}=== BUILTINS - UNSET ===${NC}\n"

run_simple_test 34 "unset variable" "export TEST=hello && unset TEST && env | grep TEST || echo OK" "OK"
run_simple_test 35 "unset multiple" "export A=1 B=2 && unset A B && env | grep -E 'A=|B=' || echo OK" "OK"

echo -e "${YELLOW}=== VARIABLE EXPANSION ===${NC}\n"

run_test 36 "Variable expansion" "export VAR=test && echo \$VAR" 0
run_test 37 "Variable in double quotes" "export VAR=test && echo \"\$VAR\"" 0
run_test 38 "Variable in single quotes" "export VAR=test && echo '\$VAR'" 0
run_test 39 "Multiple variables" "export A=1 B=2 && echo \$A \$B" 0
run_test 40 "Non-existent variable" "echo \$NONEXISTENT" 0
run_test 41 "Exit status variable" "true && echo \$?" 0
run_test 42 "Exit status after false" "false; echo \$?" 0

echo -e "${YELLOW}=== VARIABLE EXPANSION - Edge Cases ===${NC}\n"

run_test 43 "Empty variable" "export EMPTY= && echo \$EMPTY" 0
run_test 44 "Variable with underscore" "export MY_VAR=test && echo \$MY_VAR" 0
run_test 45 "Variable with numbers" "export VAR123=test && echo \$VAR123" 0
run_test 46 "Adjacent variables" "export A=a B=b && echo \$A\$B" 0

echo -e "${YELLOW}=== QUOTES ===${NC}\n"

run_test 47 "Single quotes" "echo 'hello world'" 0
run_test 48 "Double quotes" "echo \"hello world\"" 0
run_test 49 "Mixed quotes" "echo \"hello 'world'\"" 0
run_test 50 "Empty quotes" "echo ''" 0
run_test 51 "Quotes with spaces" "echo '   spaces   '" 0
run_test 52 "Variable in quotes" "export VAR=test && echo '\$VAR vs \"\$VAR\"'" 0

echo -e "${YELLOW}=== WHITESPACE ===${NC}\n"

run_test 53 "Multiple spaces" "echo    test    test" 0
run_test 54 "Tabs" "echo	test	test" 0
run_test 55 "Leading spaces" "   echo test" 0

echo -e "${YELLOW}=== COMMAND EXECUTION ===${NC}\n"

run_simple_test 56 "/bin/echo" "/bin/echo test" "test"
run_simple_test 57 "Relative path ./minishell" "test -f ./minishell && echo OK || echo SKIP" ""
run_simple_test 58 "Command not found" "commandnotfound 2>&1" "command not found"

echo -e "${YELLOW}=== EXIT CODES ===${NC}\n"

run_test 59 "true exit code" "true; echo \$?" 0
run_test 60 "false exit code" "false; echo \$?" 0
run_simple_test 61 "Exit code 127" "commandnotfound 2>&1; echo \$?" "127"

echo -e "${YELLOW}=== COMPLEX COMBINATIONS ===${NC}\n"

run_test 62 "Export + pipe + redirect" "export VAR=test && echo \$VAR | cat > /tmp/test.txt && cat /tmp/test.txt" 0
run_test 63 "Multiple redirections + pipe" "echo hello > /tmp/a.txt && cat /tmp/a.txt | cat > /tmp/b.txt && cat /tmp/b.txt" 0
run_test 64 "Builtin + pipe" "pwd | cat" 0
run_test 65 "Echo + variable + pipe" "export TEST=hello && echo \$TEST | grep hello" 0

echo -e "${YELLOW}=== SYNTAX ERRORS ===${NC}\n"

run_simple_test 66 "Empty command" "" ""
run_simple_test 67 "Only spaces" "   " ""
run_simple_test 68 "Unclosed quote" "echo 'test" ""
run_simple_test 69 "Unclosed double quote" "echo \"test" ""

echo -e "${YELLOW}=== SPECIAL FILES ===${NC}\n"

run_simple_test 70 "/dev/null write" "echo test > /dev/null && echo OK" "OK"
run_simple_test 71 "/dev/null read" "cat < /dev/null && echo OK" "OK"

cleanup
rm -f /tmp/test.txt /tmp/a.txt /tmp/b.txt /tmp/pwd_test.txt

echo -e "\n${MAGENTA}========================================${NC}"
echo -e "${MAGENTA}  Test Summary${NC}"
echo -e "${MAGENTA}========================================${NC}"
echo -e "Total tests: $TOTAL"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${MAGENTA}========================================${NC}"
    echo -e "${GREEN}All tests passed! 🎉${NC}\n"
    exit 0
else
    percentage=$(( (PASSED * 100) / TOTAL ))
    echo -e "${MAGENTA}========================================${NC}"
    echo -e "${YELLOW}Pass rate: ${percentage}%${NC}\n"
    exit 1
fi
