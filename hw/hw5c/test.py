#!/bin/python3.7

def left_right_binary_exponentiation(a, B):
  prod = 1
  for i in range(len(B), 0, -1):
    if i == len(B):
      prod = a
      continue
    prod *= prod
    if B[i] == 1:
      prod = prod * a
  return prod

print(left_right_binary_exponentiation(3, []))
