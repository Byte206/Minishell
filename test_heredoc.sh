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
MINISHELL="./minishell"

# Function to create heredoc input and run test
run_heredoc_test() {
    local test_num=$1
    local description=$2
    local heredoc_input=$3
    local expected=$4
    
    TOTAL=$((TOTAL + 1))
    
    echo -e "${BLUE}Test $test_num:${NC} $description"
    
    # Create temporary input file with heredoc
    echo "$heredoc_input" > /tmp/heredoc_input.txt
    
    # Execute with minishell (using bash for testing, replace with your minishell)
    bash < /tmp/heredoc_input.txt > /tmp/heredoc_output.txt 2>&1
    local exit_code=$?
    
    # Check result
    if [ -n "$expected" ]; then
        if grep -q "$expected" /tmp/heredoc_output.txt 2>/dev/null || [ "$expected" == "exit_code_0" ] && [ $exit_code -eq 0 ]; then
            echo -e "${GREEN}✓ PASSED${NC}\n"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}✗ FAILED${NC}"
            echo "Expected: $expected"
            echo "Got:"
            cat /tmp/heredoc_output.txt
            echo ""
            FAILED=$((FAILED + 1))
        fi
    else
        echo -e "${YELLOW}⚠ INFO${NC}"
        echo "Output:"
        cat /tmp/heredoc_output.txt
        echo ""
        PASSED=$((PASSED + 1))
    fi
    
    # Cleanup
    rm -f /tmp/heredoc_input.txt /tmp/heredoc_output.txt
}

# Function to cleanup test files
cleanup() {
    rm -f out.txt result.txt out1.txt out2.txt temp.txt
    rm -f *.txt 2>/dev/null
}

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}  Minishell Heredoc Tests${NC}"
echo -e "${YELLOW}========================================${NC}\n"

cleanup

echo -e "${BLUE}=== BASIC HEREDOC ===${NC}\n"

# Test 1: Simple heredoc with cat
run_heredoc_test 1 "Simple heredoc" \
"cat << EOF
hola
mundo
EOF" \
"hola"

# Test 2: Heredoc without command
run_heredoc_test 2 "Heredoc without command" \
"<< EOF
test
EOF
echo 'OK'" \
"OK"

# Test 3: Heredoc with different delimiter
run_heredoc_test 3 "Different delimiter" \
"cat << END
contenido
END" \
"contenido"

# Test 4: Heredoc with empty lines
run_heredoc_test 4 "Heredoc with empty lines" \
"cat << EOF
primera

tercera
EOF" \
"primera"

echo -e "${BLUE}=== HEREDOC WITH VARIABLES ===${NC}\n"

# Test 6: Variable expansion
run_heredoc_test 6 "Variable expansion" \
"export VAR=valor
cat << EOF
\$VAR
EOF" \
"valor"

# Test 7: \$? expansion after success
run_heredoc_test 7 "\$? after true" \
"true
cat << EOF
Exit: \$?
EOF" \
"Exit: 0"

# Test 8: \$? expansion after failure
run_heredoc_test 8 "\$? after false" \
"false
cat << EOF
Exit: \$?
EOF" \
"Exit: 1"

# Test 9: Non-existent variable
run_heredoc_test 9 "Non-existent variable" \
"cat << EOF
\$NOEXISTE
EOF" \
"^$"

# Test 10: Multiple variables
run_heredoc_test 10 "Multiple variables" \
"export A=1 B=2
cat << EOF
\$A y \$B
EOF" \
"1 y 2"

echo -e "${BLUE}=== HEREDOC SPECIAL CASES ===${NC}\n"

# Test 11: Line with only $
run_heredoc_test 11 "Line with \$" \
"cat << EOF
\$
EOF" \
"^\$$"

# Test 13: Heredoc with tabs
run_heredoc_test 13 "Heredoc with tabs" \
"cat << EOF
	tab before
	and here
EOF" \
"tab before"

# Test 14: Special characters
run_heredoc_test 14 "Special characters" \
"cat << EOF
!@#%^&*()
EOF" \
"!@#%^&*()"

# Test 15: Numeric delimiter
run_heredoc_test 15 "Numeric delimiter" \
"cat << EOF123
test
EOF123" \
"test"

# Test 17: Long heredoc
run_heredoc_test 17 "Long heredoc with wc" \
"cat << EOF | wc -l
1
2
3
4
5
6
7
8
9
10
EOF" \
"10"

echo -e "${BLUE}=== HEREDOC WITH PIPES ===${NC}\n"

# Test 19: Heredoc with grep
run_heredoc_test 19 "Heredoc with grep" \
"cat << EOF | grep test
test1
not this
test2
test3
EOF" \
"test1"

# Test 20: Heredoc with sort
run_heredoc_test 20 "Heredoc with sort" \
"cat << EOF | sort
zebra
apple
banana
EOF" \
"apple"

# Test 22: Heredoc with head
run_heredoc_test 22 "Heredoc with head" \
"cat << EOF | head -2
line1
line2
line3
EOF" \
"line1"

# Test 23: Heredoc with tail
run_heredoc_test 23 "Heredoc with tail" \
"cat << EOF | tail -1
line1
line2
line3
EOF" \
"line3"

# Test 24: Complex pipeline
run_heredoc_test 24 "Complex pipeline" \
"cat << EOF | grep hello | wc -w
hello world
test
hello again
EOF" \
"4"

echo -e "${BLUE}=== HEREDOC WITH REDIRECTIONS ===${NC}\n"

# Test 30: Heredoc with output redirection
run_heredoc_test 30 "Heredoc with >" \
"cat << EOF > out.txt
content
EOF
cat out.txt" \
"content"

# Test 34: Heredoc + pipes + redirections
run_heredoc_test 34 "Heredoc + pipes + >" \
"cat << EOF | cat > out.txt
data
EOF
cat out.txt" \
"data"

# Test 35: Heredoc with >> after pipe
run_heredoc_test 35 "Heredoc + pipe + >>" \
"echo 'first' > out.txt
cat << EOF | cat >> out.txt
more
EOF
cat out.txt" \
"first"

# Test 37: Heredoc in pipeline with intermediate redirection
run_heredoc_test 37 "Complex redirection" \
"cat << EOF | cat > temp.txt
test
EOF
cat temp.txt" \
"test"

echo -e "${BLUE}=== HEREDOC EDGE CASES ===${NC}\n"

# Test 39: Empty heredoc
run_heredoc_test 39 "Empty heredoc" \
"cat << EOF
EOF
echo 'DONE'" \
"DONE"

# Test 40: Heredoc with only spaces
run_heredoc_test 40 "Heredoc with spaces" \
"cat << EOF
   
EOF
echo 'DONE'" \
"DONE"

# Test 46: Heredoc preserves format
run_heredoc_test 46 "Preserve format" \
"cat << EOF
  spaces before
	tab here
trailing spaces  
EOF" \
"spaces before"

# Test 47: Variable with underscores
run_heredoc_test 47 "Variable with _" \
"export MY_VAR=value
cat << EOF
\$MY_VAR
EOF" \
"value"

# Test 48: Numbers in variable names
run_heredoc_test 48 "Numbers in variable" \
"export VAR123=test
cat << EOF
\$VAR123
EOF" \
"test"

# Test 49: Empty vs non-existent variable
run_heredoc_test 49 "Empty vs non-existent" \
"export EMPTY=
cat << EOF
empty:\$EMPTY:
noexist:\$NOEXIST:
EOF" \
"empty::"

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
