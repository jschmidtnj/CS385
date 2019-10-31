#!/bin/python3.7

def brgc(n):
  if n == 1:
    return ['0', '1']
  l1 = brgc(n - 1)
  l2 = l1.copy()
  for i in range(len(l1)):
    l1[i] = '0' + l1[i]
    l2[i] = '1' + l2[i]
  l1.extend(l2)
  return l1

print(brgc(3))
