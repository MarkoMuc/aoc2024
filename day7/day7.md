# Day 7 of AoC 2024

This is not a generic (number of input IDs is set by a macro) nor optimized solution. 

## Statistics

- Overall time: 0:21h
    - Part 1: 0:20h
    - Part 2: 0:01h
- Difficulty: Super easy in Python.
- Notes:
    - Part 1:
        1. Wasted time making a dynamic array in C, I ran into an error where i forgot to initialize a variable, which kept causing a segmentation fault.
        2. In C the logic part was easy, but ran into overflow issues.
        3. Forgot to change `aoc_get_num` function to `uint128_t` that's why I kept getting the same wrong answer even after using `uint128_t`.
        4. Writing conditions as `if..else` when I could just do `return a == b` just takes longer and more error prone. I keep doing it for no reason.
        5. Ended up doing it in Python.
    - Part 2:
        1. Doing it in Python was again super easy.
        2. In C I was still running into an overflow.
        3. Forgot to change `aoc_get_num` function to `uint128_t` that's why I kept getting the same wrong answer even after using `uint128_t`.
