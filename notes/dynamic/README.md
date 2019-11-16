# use it or lose it

## coin row

```python
def coin_row(c):
  def coin_row_helper(c, memo):
    if n <= 0:
      return 0
    if n in memo:
      return memo[n]
    val = max(c[n] + coin_row_helper(n - 2, memo), coin_row_helper(n - 1, memo))
    memo[n] = val
    return val
  c = [0] + c # used to keep indexing consistent
  return coin_row_helper(len(c) - 1, {})
```

0. make helper function, pass in an empty dictionary
1. if key in dictionary, return that value
2. do work recursively and store result in local variable
3. store result in dictionary and return result

- to make a recursive algorithm not recursive, you can typically use an array
- to create a maze coin row tester, create a 2d array and add 1 whenever there's a coin
  - save for the rest of the array going to the left and down - the max. then backtrack and go with the max cycling back up
  - runtime to generate table: $\theta(m \cdot n)$
  - to backtrack: $\theta(m + n)$

## knapsack problem

| item | weight | value | value / weight |
|------|--------|-------|----------------|
| 1    | 3      | 7     | 2 1/3          |
| 2    | 2      | 4     | 2              |
| 3    | 2      | 4     | 2              |

- 0 - 1 knapsack problem
- 1 <= i <= n is the item, wi is the weight of the ith item, vi is the value of the ith item
- 1 <= j <= w, j is the knapsack capacity
- lose_it = F(i - 1, j)
- use_it = vi + F(i - 1, j - wi)
- base case:
  - F(0, j) = 0 for j >= 0
  - F(i, 0) = 0 for i <= 0

| item | weight | value |
|------|--------|-------|
| 1    | 2      | 12    |
| 2    | 1      | 10    |
| 3    | 3      | 20    |
| 4    | 2      | 15    |

Recursive definition:

- F(i, j) = max(lose_it, use_it) if room left j>= wi
- lose_it if no room left j < wi

| iW | 0 | 1  | 2  | 3  | 4  | 5  |
|----|---|----|----|----|----|----|
| 0  | 0 | 0  | 0  | 0  | 0  | 0  |
| 1  | 0 | 0  | 12 | 12 | 12 | 12 |
| 2  | 0 | 10 | 12 | 22 | 22 | 22 |
| 3  | 0 | 10 | 12 | 22 | 30 | 32 |
| 4  | 0 | 10 | 15 | 25 | 30 | 37 |

- 37 - above is 32 (not the same), so I used 5
  - weight is 2 -> move back 2 to 22
  - row is the total weight
  - column is the item number
- if it's the same as above, you lose it (22 to 22) from 3 to 2
- so the only one not used is 3
- this is theta(n * w) for creating the 2d array, back-tracking is O(n) - not n + w because you don't necessarily visit all w spots
