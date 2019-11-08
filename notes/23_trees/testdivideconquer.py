#!/bin/python3.7

def Horner(P, x):
  '''
  evaluates a polynomial at a given point by Horner's ryle
  input: an array P[0...n] of coefficients of a polynomial
  of degree n, stored from the lowest to the highest, and
  a number x
  output: the value of the polynomial of x
  '''
  p = P[-1]
  i = len(P) - 2
  while i >= 0:
    p = x * p + P[i]
    i -= 1
  return p

res = Horner([2, 1], 2)
print(res)

def leftRightBinaryExponentiation(a, B):
  '''
  computes a^n
  input: a number 'a' and a list b(n) of binary digits bI ... bi ... b0
  '''
  product = 1
  i = len(B) - 1
  while i >= 0:
    if B[i] == 1:
      product = product * a
    a = a * a
    i -= 1
  return product

in2 = 2
thepow = [1, 1, 0, 1]
thepowactual = 13
res2 = leftRightBinaryExponentiation(in2, thepow)
print(res2)
print(in2 ** thepowactual)
