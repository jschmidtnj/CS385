#!/bin/python

def staircase_count(stairs):
  if stairs < 0:
    return 0
  if stairs is 0:
    return 1
  return staircase_count(stairs - 1) + staircase_count(stairs - 2) + staircase_count(stairs - 3)

# print(staircase_count(5))

# O(3^n) function:
def get_ways(num_stairs):
  ways = []
  if num_stairs <= 0:
    ways.append([])
  else:
    for i in range(1, 4):
      if num_stairs >= i:
        result = get_ways(num_stairs - i)
        for j in range(len(result)):
          result[j].append(i)
        ways += result
  return ways

# print(len(get_ways(21)))

# O(3^n) function:
# this just isn't working
def get_ways_dyn(num_stairs, store):
  ways = []
  if num_stairs <= 0:
    ways.append([])
  else:
    for i in range(1, 4):
      if num_stairs >= i:
        if num_stairs in store:
          result = store[num_stairs - i]
        else:
          result = get_ways_dyn(num_stairs - i, store)
          # store[num_stairs - i] = result
        for j in range(len(result)):
          result[j].append(i)
        ways += result
  return ways

print(get_ways_dyn(5, {}))

def countWaysFib(n, m):
  res = [0 for _ in range(n)] # Creates list res with all elements 0
  res[0],res[1] = 1,1
  for i in range(2,n):
    j = 1
    while j<=m and j<=i:
      res[i] = res[i] + res[i-j]
      j += 1
  return res[n-1]

# print(countWaysFib(5 + 1, 3))
