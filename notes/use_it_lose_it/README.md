# use it or lose it

## coin row

```python
def coin_row(c):
  def coin_row_helper(c, memo):
    if n <= 0:
      return 0
    if n in memo:
      return c[n]
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
