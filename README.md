# push_swap

![42 Logo](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTXfAZMOWHDQ3DKE63A9jWhIqQaKcKqUIXvzg&s)

**push_swap** is a project from 42 School that challenges you to sort data using a limited set of operations. In this project, you will implement an efficient algorithm that sorts a stack of integers using two stacks (A and B) and a predefined set of instructions. The main objective is to minimize the number of operations needed to achieve a sorted stack.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)

## Description

The **push_swap** project involves creating a program that sorts a list of integers using two stacks and a restricted set of operations. The project typically consists of two components:

- **push_swap**: Generates a sequence of operations that, when applied to the initial stack, will sort the numbers.
- **checker** (optional): Takes a list of operations and verifies if applying them to the initial stack results in a sorted stack.

The allowed operations are:

- `sa` (swap a): Swap the first two elements at the top of stack A.
- `sb` (swap b): Swap the first two elements at the top of stack B.
- `ss`: Perform `sa` and `sb` simultaneously.
- `pa` (push a): Move the top element of stack B to the top of stack A.
- `pb` (push b): Move the top element of stack A to the top of stack B.
- `ra` (rotate a): Shift all elements of stack A upward by one (the first element becomes the last).
- `rb` (rotate b): Shift all elements of stack B upward by one.
- `rr`: Perform `ra` and `rb` simultaneously.
- `rra` (reverse rotate a): Shift all elements of stack A downward by one (the last element becomes the first).
- `rrb` (reverse rotate b): Shift all elements of stack B downward by one.
- `rrr`: Perform `rra` and `rrb` simultaneously.

## Features

- **Efficient Sorting**: Design an algorithm that sorts integers with a minimal number of operations.
- **Operation Optimization**: Focus on reducing the total count of moves required.
- **Two-Stack Approach**: Leverage stack A and stack B to implement the sorting process.
- **Optional Checker**: Validate the correctness of the operations sequence using the checker program.

## Requirements

- **C Compiler** (e.g., `gcc`)
- **Make** (for building the project)
- **Unix-based Operating System** (Linux, macOS)

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/yourusername/push_swap.git
    ```
2. **Navigate to the project directory:**
    ```bash
    cd push_swap
    ```
3. **Compile the project using Make:**
    ```bash
    make
    ```
    This will compile the `push_swap` executable and, if implemented, the `checker` executable.

## Usage

### Running push_swap

Provide a list of integers as arguments to sort:
```bash
./push_swap 3 2 1 6 5 8
```
The program will output a sequence of operations that will sort the input numbers.

### Running checker (Optional)
If you have implemented the checker program, you can pipe the operations from push_swap into checker to verify the result:
```bash
./push_swap 3 2 1 6 5 8 | ./checker 3 2 1 6 5 8
```
The checker will output OK if the sequence sorts the stack correctly, or KO if it does not.

## How It Works
1. Input Parsing: The program validates and parses the list of integers provided as command-line arguments.
2. Sorting Algorithm: Using two stacks (A and B), the algorithm computes an optimized sequence of operations that sorts the numbers.
3. Operation Execution: Each operation manipulates the stacks, gradually moving the elements into sorted order.
4. Output Generation: The sequence of operations is printed to standard output.
5. Validation: (Optional) The checker program can simulate the operations to verify that the final stack is sorted.

