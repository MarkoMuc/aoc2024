# Day 6 of AoC 2024

This is not a generic (number of input IDs is set by a macro) nor optimized solution. 

## Statistics

- Overall time: 3:05h
    - Part 1: 00:42h
    - Part 2: 02:23h
- Difficulty: Easy.
- Notes:
    - Part 1:
        1. Didn't make sure to only count distinct positions.
        2. Testing code I should know works by now.
        3. Going for a recursive version when it was not needed.
        4. Recursive version was also close to being correct, but I decided to go with an iterative version for no good reason.
        5. With the recursive version I used `counter++` instead of `++counter` or `counter+1` which was one of the errors.
        6. I'm still not sure why the counter was wrong at times.
    - Part 2:
        1. I wanted to take a shortcut, that ended up costing me hours of work. Instead of just creating a dynamic array I used a static direction hoping I wouldn't run into an error. Which I did, in 2 cases I found a cycle where I shouldn't have. I'm still not exactly sure in which case my logic breaks, but it seems that there exists some cases where it does.
        2. I made a mistake while writing the dynamic array, I forgot to pass by reference when adding elements in function `add_steps`.
        3. Would be worth it to create a personal library for creating generic dynamic arrays.
