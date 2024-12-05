# Day 5 of AoC 2024

This is not a generic (number of input IDs is set by a macro) nor optimized solution. 

## Statistics

- Overall time: 1:00h
    - Part 1: 00:47h
    - Part 2: 00:13h
- Difficulty: Easy.
- Notes:
    - Part 1:
        1. Could have read the instructions faster and wrote the code faster.
        2. Used the wrong indexes for accessing the `rules` array and didn't even use the `nums` array the first time.
        3. Writing down the rules would have also helped.
        4. The biggest error was miscalculating the index of the middle element.
    - Part 2:
        1. Wanted to collapse the two `if`s into one, when it doesn't matter.
        2. Didn't set `return 0` for lines that were correct, I copied it too fast.
        3. Luckily I managed to find the error fast.
