# Notes

An algorithm is a sequence of unambiguous instructions for solving a problem, i.e. for obtaining a required output for any legitimate inut in a finite amount of time.

1. The nonambiguity requirement for each step of an algorithm cannot be compromised.
2. The range of inputs for which an algorithm works has to be specified carefully.
3. The same algorithm can be represented in several different ways.
4. There may exist several algorithms for solving the same problem.

## constraints

### Big O

essentially an upper bound for how slow an algorithm is
---

O(g(n)) = {f(n): exists positive constants c and n0, such that
    0 <= f(n) <= c*g(n) for all n >= n0}

n0 starts when f(n) = g(n) the last time (last intersection of the graphs)  
this is when it starts to hold

### omega for lower bound

Omega(g(n)) = {f(n): exists positive constants c and n0, such that
    0 <= c*g(n) <= f(n) for any n >= n0}

lower bound for performance / runtime
---

n0 also starts with last intersection

### theta

Theta(g(n)) = {f(n): exists positive constants c and n0, such that
    0 <= c1*g(n) <= f(n) <= c2*g(n) for all n >= n0}

type bound - bounded above and below
---

n0 also starts with last intersection

### notes

always use theta first because it is the most restrictive. theta gives the most information. then look to O if you cannot get theta. very rarely do we use omega

## O-notation

100n + 5 E O(n^2)? yes
100n + 5 <= 100n + n(for all n >= 5) = 101n <= 101n^2           | C = 101, n0 = 5

OR----->

100n + 5 <= 100n + 5n(for all n >= 1) = 105n <= 105n^2          | C = 105, n0 = 1

OR-----> (minimize c - this is the typical solution)

100n + 5 <= 1n^2 (for all n >= 101)                             | C = 1, n0 = 101

- for upper bound (O) we want to minimize c
- for omega we want to make c as large as possible

### ex 2

find an upper bound for f(n) = 3n + 8

3n + 8 <= 4*n for all n >= 8                                    | C = 4, n0 = 8
3n + 8 <= 11*n for all n >= 1                                   | C = 11, n0 = 1
f(n) = n^2 + 1 <= 2*n^2 for all n >= 1                          | C = 2, n0 = 1

## Omega-notation

n^3 E Omega(n^2)
c*n^2 <= n^3                                                    | C = 1, n0 = 1

try: find a lower bound for f(n) = 5n^2
Omega(n^2)
c*n^2 <= 5n^2                                                   | C = 5, n0 = 1

Does f(n) = 100n + 5 E Omega(n^2)?
there exists positive constants c and n0 such that 0 <= cn^2 <= 100n + 5

100n + 5 <= 100n + 5n(for any n >= 1) = 105n

cn^2 <= 105n
cn^2 - 105n <= 0
n(cn - 105) <= 0
n = 0, cn - 105 = 0
n = 105 / c

then draw number line


   X               -                +
<======|=======================|==========>
       0                      105/c

X contradiction - n cannot be <= a constant, holds
only for n <= 105/c

## Theta-notation

### ex1

1/2*n(n-1) E Theta(n^2) ? yes

prove upper bound first:

1/2*n(n-1) = 1/2n^2 - 1/2n <= 1/2n^2 for any n >= 1

prove lower bound next:

1/2*n(n-1) = 1/2n^2 - 1/2n >= 1/2n^2 - (1/2n)(1/2n) = 1/4n^2 for any n >= 2

c1 = 1/4, c2 = 1/2, n0 =  2

### ex2

ex. is n E Theta(n^2)? no

c1*n^2 <= n <= c2*n^2

c1*n^2 <= n

n^2 <= n/c1

n <= 1/c1

X - cannot be <= a constant

## general math

### logarithms

1. loga(1) = 0
2. loga(a) = 1
3. loga(x^y) = yloga(x)
4. loga(xy) = loga(x) + loga(y)
5. loga(x / y) = loga(x) - loga(y)
6. a^(logb(x)) = x^(logb(a))
7. loga(x) = logb(x) / logb(a)

### combinatorics

1. number of permutations of an n-element set is P(n) = n!
2. number of k-combinations of an n-element set is C(n, k) = n!/(k!(n-k)!)
3. number of subsets of an n-element set is 2^n

### summations

- sum from i = 1 to n of c*i = c * summation(i)
- sum from i = C to n of i = sum from i=0 to n-c of (i + c)
- sum from i = C to N of i = sum from i = 0 to n of i - sum from i = 0 to c - 1 of i
- sum from i = 1 to n of A + B = sum from i to n of a + sum from i to n of b
- sum from i = 0 to n of n - 1 = sum from i = 0 to n of i
- sum from i = 1 to n of 1 = n
- sum from i = 1 to n of c is c * n
- sum from i = 1 to n of i = n*(n+1) / 2
- sum from i = 1 to n of i^2 is n(n+1)(2n+1) / 6
- sum from i = 0 to n of a^i = (a^n+1 - 1) / (a - 1) (a != 1)
- sum from i = 1 to n of 1/n is about log(n) [actually ln(n) + gamma]

### random

log2(n) is the same as lg(n) in comp sci

## 9/11/19: quiz tomorrow

- on makefiles and the commandline.
- know the flags and how they work in the standard makefile
- not on c++ at all
