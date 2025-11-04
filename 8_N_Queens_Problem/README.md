# N-Queens Problem

## Problem Description

The N-Queens problem is a classic backtracking problem where N chess queens must be placed on an N×N chessboard such that no two queens can attack each other.

## Constraints

- No two queens can be in the same row
- No two queens can be in the same column
- No two queens can be on the same diagonal

## Algorithm

This implementation uses **Backtracking** with the following optimizations:

1. **Incremental Row Placement**: Place one queen per row, reducing search space
2. **Efficient Conflict Detection**: Check only previous rows for conflicts
3. **Early Pruning**: Abandon invalid placements immediately
4. **Mathematical Diagonal Check**: Use `abs(row1 - row2) == abs(col1 - col2)` for diagonal detection

## Input Format

```
N
```

Where N is the size of the chessboard (1 ≤ N ≤ 20)

## Output Format

- Total number of solutions
- First few solutions displayed as boards
- All solutions in compact format

## Time Complexity

- **Worst Case**: O(N!)
- **With Pruning**: Significantly better in practice
- **Space Complexity**: O(N) for recursion stack

## Example

For N = 8:

```
Input: 8
Output: 92 solutions
```

## Compilation and Execution

```bash
g++ -o n_queens n_queens.cpp -std=c++11
./n_queens
```
