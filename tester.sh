#!/bin/bash
errors=0  # Error counter

# Function to run functional tests via checker_linux
run_test() {
    args="$1"
    expected="$2"

    # Get the output of test via checker_linux
    checker_output=$(./push_swap $args 2>&1 | ./checker_linux $args 2>&1)
    if [ "$checker_output" == "$expected" ]; then
        echo "✅ OK: ARG=\"$args\""
    else
        echo "❌ FAIL: ARG=\"$args\""
        echo "   Expected: \"$expected\""
        echo "   Got:    \"$checker_output\""
        errors=$((errors + 1))
    fi
}

# Function to run empty input tests
run_empty_input_tests() {
    expected_output="$1"

    # 1️⃣ Check the output of empty input
    empty_output=$(./push_swap 2>&1)

    if [ "$empty_output" == "$expected_output" ]; then
        echo "✅ OK (Empty input correctly returns \"$expected_output\")"
    else
        echo "❌ FAIL (Empty input): Expected \"$expected_output\", but got:"
        echo "\"$empty_output\""
        errors=$((errors + 1))
    fi

    # 2️⃣ Check memory errors in empty input
    vg_output=$(valgrind --leak-check=no --error-exitcode=42 ./push_swap 2>&1)

    if echo "$vg_output" | grep -q "ERROR SUMMARY: 0 errors"; then
        echo "✅ OK (No Memory Errors in empty input test)"
    else
        echo "❌ FAIL (Memory Errors in empty input test)"
        echo "$vg_output" | grep "ERROR SUMMARY:"
        errors=$((errors + 1))
    fi

    # 3️⃣ Check memory leaks in empty input
    vg_output=$(valgrind --leak-check=full --show-leak-kinds=all \
        --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap 2>&1)

    total_heap=$(echo "$vg_output" | grep "total heap usage:")
    allocs=$(echo "$total_heap" | sed -E 's/.*total heap usage: ([0-9]+) allocs,.*/\1/')
    frees=$(echo "$total_heap" | sed -E 's/.*allocs, ([0-9]+) frees,.*/\1/')

    if [ -z "$allocs" ] || [ -z "$frees" ]; then
        echo "❌ FAIL (Memory Leaks in empty input test)"
        errors=$((errors + 1))
    elif [ "$allocs" -eq "$frees" ]; then
        echo "✅ OK (No Memory Leaks in empty input test)"
    else
        echo "❌ FAIL (Memory Leaks in empty input test) - $total_heap"
        errors=$((errors + 1))
    fi
}

# Function to run sorted tests
run_sorted_test() {
    args="$1"
    output=$(./push_swap $args 2>&1)
    if [ -z "$output" ]; then
        echo "✅ OK (Already Sorted): ARG=\"$args\""
    else
        echo "❌ FAIL (Already Sorted): ARG=\"$args\""
        echo "   Expected no output (already sorted), but got:"
        echo "\"$output\""
        errors=$((errors + 1))
    fi
}

# Function to run memory errors tests via Valgrind(no leaks check)
run_valgrind_memory_errors_test() {
    args="$1"

    # Get the output of Valgrind
    vg_output=$(valgrind --leak-check=no --error-exitcode=42 ./push_swap $args 2>&1)
    if echo "$vg_output" | grep -q "ERROR SUMMARY: 0 errors"; then
        echo "✅ OK (No Memory Errors): ARG=\"$args\""
    else
        echo "❌ FAIL (Memory Errors): ARG=\"$args\""
        echo "$vg_output" | grep "ERROR SUMMARY:"
        errors=$((errors + 1))
    fi
}

# Function to run memory leaks tests via Valgrind
run_valgrind_memory_leaks_test() {
    args="$1"
    vg_output=$(valgrind --leak-check=full --show-leak-kinds=all \
        --errors-for-leak-kinds=all --error-exitcode=42 ./push_swap $args 2>&1)
    
    # Get the total heap usage
    total_heap=$(echo "$vg_output" | grep "total heap usage:")
    # Get the number of allocs and frees
    allocs=$(echo "$total_heap" | sed -E 's/.*total heap usage: ([0-9]+) allocs,.*/\1/')
    frees=$(echo "$total_heap" | sed -E 's/.*allocs, ([0-9]+) frees,.*/\1/')
    
    if [ "$allocs" -eq "$frees" ]; then
        echo "✅ OK (No Memory Leaks): ARG=\"$args\""
    else
        echo "❌ FAIL (Memory Leaks): ARG=\"$args\" - $total_heap"
        errors=$((errors + 1))
    fi
}

# Function to run random tests with random numbers
run_random_tests() {
    num_tests="$1"  # The number of tests
    num_numbers="$2" # The number of numbers in each test

    echo ""
    echo "(Sorting $num_numbers values)..."

    for i in $(seq 1 $num_tests); do
        # Generate random unique numbers in range [INT_MIN, INT_MAX]
        ARG=$(python3 -c "import random; print(' '.join(map(str, random.sample(range(-2147483648, 2147483647), $num_numbers))))")

        # Check if the output is sorted
        checker_output=$(./push_swap $ARG 2>&1 | ./checker_linux $ARG 2>&1)
        # Count the number of operations
        operation_count=$(./push_swap $ARG | wc -l)

        if [ "$checker_output" == "OK" ]; then
            echo "✅ OK (Test #$i, Args count: $num_numbers): Ops count: $operation_count"
        else
            echo "❌ FAIL (Test #$i, Args count: $num_numbers): Ops count: $operation_count"
            echo "   ARG=\"$ARG\""
            echo "   Expected: \"OK\""
            echo "   Got: \"$checker_output\""
            errors=$((errors + 1))
        fi
    done
}

# Main tests
echo "🚀 [Phase 1] Functional tests via checker_linux..."
echo ""
echo "✅ [Check OK] checking tests that should return OK [Check OK] ✅"
run_test "1 3 5 +9 20 -4 50 60 04 08" "OK"
run_test "3 4 6 8 9 74 -56 +495" "OK"
run_test "95 99 -9 10 9" "OK"
run_test "2147483647 2 4 7" "OK"
run_test "99 -2147483648 23 545" "OK"
run_test "2147483647 843 56544 24394" "OK"
echo ""
echo "❎ [Check Error] Checking tests that should return Error [Check Error] ❎"
run_test "1 3 dog 35 80 -3" "Error"
run_test "a" "Error"
run_test "1 2 3 5 67b778 947" "Error"
run_test "12 4 6 8 54fhd 4354" "Error"
run_test "1 -- 45 32" "Error"
run_test "1 3 58 9 3" "Error"
run_test "3 03" "Error"
run_test "49 128 50 38 49" "Error"
run_test "54867543867438 3" "Error"
run_test "-2147483647765 4 5" "Error"
run_test "214748364748385 28 47 29" "Error"

# Empty input tests
echo ""
echo "🚀 [Phase 2] Testing push_swap with empty input..."
echo ""
run_empty_input_tests "Error: no arguments"

echo ""
echo "🚀 [Phase 3] Testing  push_swap with already sorted input..."
echo ""
run_sorted_test "1 2 3 4 5"
run_valgrind_memory_errors_test "1 2 3 4 5"
run_valgrind_memory_leaks_test "1 2 3 4 5"
run_sorted_test "-10 0 7 12 100"
run_valgrind_memory_errors_test "-10 0 7 12 100"
run_valgrind_memory_leaks_test "-10 0 7 12 100"


# Memory errors tests
echo ""
echo "🚀 [Phase 4] Memory Errors tests via Valgrind..."
echo ""
echo "✅ [Check OK] checking tests that should return OK [Check OK] ✅"
run_valgrind_memory_errors_test "1 3 5 9 20 -4 50 60 4 8"
run_valgrind_memory_errors_test "3 4 6 8 9 74 -56 495"
run_valgrind_memory_errors_test "95 99 -9 10 9"
run_valgrind_memory_errors_test "2147483647 2 4 7"
run_valgrind_memory_errors_test "99 -2147483648 23 545"
run_valgrind_memory_errors_test "2147483647 843 56544 24394"
echo ""
echo "❎ [Check Error] Checking tests that should return Error [Check Error] ❎"
run_valgrind_memory_errors_test "1 3 dog 35 80 -3"
run_valgrind_memory_errors_test "a"
run_valgrind_memory_errors_test "1 2 3 5 67b778 947"
run_valgrind_memory_errors_test "12 4 6 8 54fhd 4354"
run_valgrind_memory_errors_test "1 -- 45 32"
run_valgrind_memory_errors_test "1 3 58 9 3"
run_valgrind_memory_errors_test "3 03"
run_valgrind_memory_errors_test "49 128 50 38 49"
run_valgrind_memory_errors_test "54867543867438 3"
run_valgrind_memory_errors_test "-2147483647765 4 5"
run_valgrind_memory_errors_test "214748364748385 28 47 29"

# Memory leaks tests
echo ""
echo "🚀 [Phase 5] Memory Leaks tests via Valgrind..."
echo ""
echo "✅ [Check OK] checking tests that should return OK [Check OK] ✅"
run_valgrind_memory_leaks_test "1 3 5 9 20 -4 50 60 4 8"
run_valgrind_memory_leaks_test "3 4 6 8 9 74 -56 495"
run_valgrind_memory_leaks_test "95 99 -9 10 9"
run_valgrind_memory_leaks_test "2147483647 2 4 7"
run_valgrind_memory_leaks_test "99 -2147483648 23 545"
run_valgrind_memory_leaks_test "2147483647 843 56544 24394"
echo ""
echo "❎ [Check Error] Checking tests that should return Error [Check Error] ❎"
run_valgrind_memory_leaks_test "1 3 dog 35 80 -3"
run_valgrind_memory_leaks_test "a"
run_valgrind_memory_leaks_test "1 2 3 5 67b778 947"
run_valgrind_memory_leaks_test "12 4 6 8 54fhd 4354"
run_valgrind_memory_leaks_test "1 -- 45 32"
run_valgrind_memory_leaks_test "1 3 58 9 3"
run_valgrind_memory_leaks_test "3 03"
run_valgrind_memory_leaks_test "49 128 50 38 49"
run_valgrind_memory_leaks_test "54867543867438 3"
run_valgrind_memory_leaks_test "-2147483647765 4 5"
run_valgrind_memory_leaks_test "214748364748385 28 47 29"

# Random tests(benchmark for project evaluation)
echo ""
echo "🚀 [Phase 6] Randomized tests..."
run_random_tests 5 3 # Test with 3 numbers 5 times
run_random_tests 5 4 # Test with 4 numbers 5 times
run_random_tests 5 5 # Test with 5 numbers 5 times
run_random_tests 5 100 # Test with 100 numbers 5 times
run_random_tests 5 500 # Test with 500 numbers 5 times

# Print summary
echo ""
if [ "$errors" -gt 0 ]; then
    echo "⚠️  Completed with $errors errors!"
else
    echo "🎉 All tests passed successfully!"
fi
