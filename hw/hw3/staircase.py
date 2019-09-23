#!/bin/python

def staircase_count(stairs):
  if stairs < 0:
    return 0
  if stairs is 0:
    return 1
  return staircase_count(stairs - 1) + staircase_count(stairs - 2) + staircase_count(stairs - 3)

print(staircase_count(5))

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

print(len(get_ways(21)))
