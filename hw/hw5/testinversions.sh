#!/bin/bash

file=inversioncounter.cpp
MAXTIME="8.0"

if [ ! -f "$file" ]; then
    echo -e "Error: File '$file' not found.\nTest failed."
    exit 1
fi

num_right=0
total=0
line="________________________________________________________________________"
compiler=
interpreter=
language=
extension=${file##*.}
if [ "$extension" = "py" ]; then
    if [ ! -z "$PYTHON_PATH" ]; then
        interpreter=$(which python.exe)
    else
        interpreter=$(which python3.2)
    fi
    command="$interpreter $file"
    echo -e "Testing $file\n"
elif [ "$extension" = "java" ]; then
    language="java"
    command="java ${file%.java}"
    echo -n "Compiling $file..."
    javac $file
    echo -e "done\n"
elif [ "$extension" = "c" ] || [ "$extension" = "cpp" ]; then
    language="c"
    command="./${file%.*}"
    echo -n "Compiling $file..."
    results=$(make 2>&1)
    if [ $? -ne 0 ]; then
        echo -e "\n$results"
        exit 1
    fi
    echo -e "done\n"
fi

timeout() {
    time=$1

    # start the command in a subshell to avoid problem with pipes
    # (spawn accepts one command)
    cmd="/bin/bash -c \"$2\""

    expect -c "set echo \"-noecho\"; set timeout $time; spawn -noecho $cmd; expect timeout { exit 1 } eof { exit 0 }"    

    if [ $? -eq 1 ]; then
        return 0
    fi
    return 1
}

run_test_args() {
    (( ++total ))
    echo -n "Running test $total..."
    expected=$3
    local ismac=0
    date --version >/dev/null 2>&1
    if [ $? -ne 0 ]; then
       ismac=1
    fi
    local start=0
    if (( ismac )); then
        start=$(python -c 'import time; print time.time()')
    else
        start=$(date +%s.%N)
    fi
(cat << ENDOFTEXT
$2
ENDOFTEXT
) > input.txt
    if timeout $MAXTIME "cat input.txt | $command $1 2>&1 | tr -d '\r' > tmp.txt"; then
        echo "failure [timed out after $MAXTIME seconds]"
    else
        received=$(cat tmp.txt)
        local end=$(date +%s.%N)
        if (( ismac )); then
            end=$(python -c 'import time; print time.time()')
        else
            end=$(date +%s.%N)
        fi
        local elapsed=$(echo "scale=3; $end - $start" | bc | awk '{printf "%.3f", $0}') 
        if [ "$expected" != "$received" ]; then
            echo -e "failure\n\nExpected$line\n$expected\n"
            echo -e "Received$line\n$received\n"
        else
            echo "success [$elapsed seconds]"
            (( ++num_right ))
        fi
    fi
    rm -f tmp.txt
}

run_test_args "" "x 1 2 3" "Enter sequence of integers, each followed by a space: Error: Non-integer value 'x' received at index 0."
run_test_args "" "1 2 x 3" "Enter sequence of integers, each followed by a space: Error: Non-integer value 'x' received at index 2."
run_test_args "lots of args" "" "Usage: ./inversioncounter [slow]"
run_test_args "average" "" "Error: Unrecognized option 'average'."
run_test_args "" "" "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."
run_test_args "" "  " "Enter sequence of integers, each followed by a space: Error: Sequence of integers not received."

# write some tests that use the 'slow' approach. Here is one example.
# You are allowed up to 8 seconds to count inversions on up to 100,000 values.
run_test_args "slow" "2" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "slow" "2 1" "Enter sequence of integers, each followed by a space: Number of inversions: 1"
run_test_args "slow" "1 2 3" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "slow" "1 2 5 4 3" "Enter sequence of integers, each followed by a space: Number of inversions: 3"
run_test_args "slow" "1 2 5 4 3 6 1 8 2 3 9" "Enter sequence of integers, each followed by a space: Number of inversions: 17"
run_test_args "slow" "6 2 8 9 8 2 3 5 1 12 9 1 -1" "Enter sequence of integers, each followed by a space: Number of inversions: 45"
run_test_args "slow" "3 2 1 2 4 5 3 -2 -5 9 3 19" "Enter sequence of integers, each followed by a space: Number of inversions: 24"
run_test_args "slow" "5 2 4 7 3 1 2 -1 5 -3 -5 4 9" "Enter sequence of integers, each followed by a space: Number of inversions: 44"
run_test_args "slow" "68 2 3 99 48 -49 2 28 19" "Enter sequence of integers, each followed by a space: Number of inversions: 20"
run_test_args "slow" "5 2 1 -4 8 9 0 -4 8 3 7" "Enter sequence of integers, each followed by a space: Number of inversions: 25"
run_test_args "slow" "7 9 3 -4 67 92 -5 -2 9 5" "Enter sequence of integers, each followed by a space: Number of inversions: 23"
run_test_args "slow" "7 8 -3 92 93 75 0 32 1 8 7" "Enter sequence of integers, each followed by a space: Number of inversions: 28"
run_test_args "slow" "8 57 -2 4 -6 9 8 29 3" "Enter sequence of integers, each followed by a space: Number of inversions: 18"
run_test_args "slow" "9 3 7 -2 -6 8 -6 2 9 25" "Enter sequence of integers, each followed by a space: Number of inversions: 19"
run_test_args "slow" "$(echo {100000..1})" "Enter sequence of integers, each followed by a space: Number of inversions: 4999950000"
run_test_args "slow" "$(echo {1..100000})" "Enter sequence of integers, each followed by a space: Number of inversions: 0"

# END slow tests

MAXTIME="1.250"

# write some tests that use the 'fast' approach. Here is one example.
# You are allowed up to 1.25 seconds to count inversions on up to 100,000 values.
run_test_args "" "2" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "" "2 1" "Enter sequence of integers, each followed by a space: Number of inversions: 1"
run_test_args "" "1 2 3" "Enter sequence of integers, each followed by a space: Number of inversions: 0"
run_test_args "" "1 2 5 4 3" "Enter sequence of integers, each followed by a space: Number of inversions: 3"
run_test_args "" "1 2 5 4 3 6 1 8 2 3 9" "Enter sequence of integers, each followed by a space: Number of inversions: 17"
run_test_args "" "6 2 8 9 8 2 3 5 1 12 9 1 -1" "Enter sequence of integers, each followed by a space: Number of inversions: 45"
run_test_args "" "3 2 1 2 4 5 3 -2 -5 9 3 19" "Enter sequence of integers, each followed by a space: Number of inversions: 24"
run_test_args "" "5 2 4 7 3 1 2 -1 5 -3 -5 4 9" "Enter sequence of integers, each followed by a space: Number of inversions: 44"
run_test_args "" "68 2 3 99 48 -49 2 28 19" "Enter sequence of integers, each followed by a space: Number of inversions: 20"
run_test_args "" "5 2 1 -4 8 9 0 -4 8 3 7" "Enter sequence of integers, each followed by a space: Number of inversions: 25"
run_test_args "" "7 9 3 -4 67 92 -5 -2 9 5" "Enter sequence of integers, each followed by a space: Number of inversions: 23"
run_test_args "" "7 8 -3 92 93 75 0 32 1 8 7" "Enter sequence of integers, each followed by a space: Number of inversions: 28"
run_test_args "" "8 57 -2 4 -6 9 8 29 3" "Enter sequence of integers, each followed by a space: Number of inversions: 18"
run_test_args "" "9 3 7 -2 -6 8 -6 2 9 25" "Enter sequence of integers, each followed by a space: Number of inversions: 19"
run_test_args "" "$(echo {100000..1})" "Enter sequence of integers, each followed by a space: Number of inversions: 4999950000"
run_test_args "" "$(echo {1..100000})" "Enter sequence of integers, each followed by a space: Number of inversions: 0"


# END fast tests

echo -e "\nTotal tests run: $total"
echo -e "Number correct : $num_right"
echo -n "Percent correct: "
echo "scale=2; 100 * $num_right / $total" | bc

if [ "$language" = "java" ]; then
    echo -e -n "\nRemoving class files..."
    rm -f *.class
    echo "done"
elif [ "$language" = "c" ]; then
    echo -e -n "\nCleaning project..."
    make clean > /dev/null 2>&1
    echo "done"
fi
