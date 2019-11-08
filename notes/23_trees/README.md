# 2-3 trees

- tree with 2 nodes and 3 nodes
- used in relational database (b + trees are actually used)
  - used because tree is not very deep - don't need to do many lookups (data is packed into nodes)
- the height should be the same everywhere (it's always height balanced)
- see [this](https://www.cs.usfca.edu/~galles/visualization/BTree.html)

## transformers

Transform and Conquer - polynomial evaluation faster (by factoring)  
-> this takes a lot less multiplication steps

- $p(x) = 2 \cdot x^4 - x^3 + 3 \cdot x^2 + x - 5$
- $p(x) = x \cdot (2 \cdot x^3 - x^2 + 3 \cdot x + 1) - 5$
- $p(x) = x \cdot (x \cdot (2 \cdot x^2 - x + 3) + 1) - 5$
- $p(x) = x \cdot (x \cdot (x \cdot (2 \cdot x - 1) + 3) + 1) - 5$

### Horner's rule for evaluating a polynomial

```python
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
```

### binary exponentiation

- computing $a^n$
- let $n = b_{I} ... b_{i} ... b_{0}$
- $p(x) = b_I \cdot x^I ... b_i \cdot x^i ... b_0$ where x=2
- $13 = 1 \cdot 2^3 + 1 \cdot 2^2 + 0 \cdot 2^1 + 1 \cdot 2^0$
  - binary = 1101
- ...

```python
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
```
