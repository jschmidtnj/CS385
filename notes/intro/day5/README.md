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
