# The 2022 ICPC Programming Contest University of Science, VNU-HCM
**09/10/2022 *(12h - 5h)***

**Solved**: 10/13 problems

Problem statement: [Problem](Problem)

Our team code: [Code](Code)

## Solution

### A
Find `shortest path - 1`, using BFS
### B
Calculate sum of all puzzles' area and divide `W` to find `H`
### C
Because $l, h \le 10^5$, Sieve of Eratosthenes to find all prime number upto $10^7$
### D
Trie, heap

*8 tries* (TLE 😥) -> use array index to implement Trie instead of pointer 😰

### E
Dynamic programming, similar LIS problem

Let `f(x) = number of choices end with number x`, the number can be placed before `x` is flip all bit of `x`

With number `x`, flip all m bit of `x`: `x ^ ((1 << m) - 1)`


### H
Math, Data structure (BIT/IT)

Compute index of the original permutation, and modify answer for each query

Query swap $(i, j)$ only affect answer in range $[i, j]$

Our solution can calculate correct answer but getting TLE because time complexity is $O(nlog^2(n))$ 😭 -> can use persistent segment tree to reduce.

### I
The Inclusion-Exclusion Principle

### J
Convert each digit to binary

### K
Because $k \le 10$ -> brute-forces generate all binary (T or F) of length k in $O(2^k)$ 

### L
Deque min-max

### M
Math, combination