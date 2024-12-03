# Day 2 of AoC 2024

This is not a generic (number of input IDs is set by a macro) nor optimized solution. 

## Statistics

- Overall time: 1:46h
    - Part 1: 00:46h
    - Part 2: 01:00h
- Difficulty: Easy.
- Notes:
    - Part 1:
        1. Consuming one character too many in `get_num()` function.
        2. Multiple small mistakes because I didn't finish code.
    - Part 2:
        1. Reusing code for part 1 and not rethinking new edge cases.
        2. Biggest mistake was assuming that the lines of instructions work independently. This resulted in resetting the `enabled` flag instead of carrying it.
