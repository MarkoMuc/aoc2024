# Day 2 of AoC 2024

This is not a generic (number of input IDs is set by a macro) nor optimized solution. 

## Statistics

- Overall time: 2:02h
- Difficulty: This one was also easy.
- Notes:
    - Part 1:
        1. Misplaced variable definition of `asc`. Should have found this issue much faster.
    - Part 2:
        1. Started trying to modify part 1 too fast. Should have thought about what are all possible cases in part 2. It ended up being a waste of time.
        2. Pay more attention to possible off by 1's.
        3. Might be better to use `while` loops instead of `for` loops when the `for` loop might need to be reset. This caused an issue where I reset the index `idx` and when the loop actually "reset" it was incremented by 1.
