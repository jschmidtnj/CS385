# practice questions 9/20

## queestion 1

x(n) = 2x(n/2) + n, x(1) = 1

1. x(n/2) = 2x(n/4) + (n/2)
   1. x(n) = 2(2x(n/4) + n/2) + n
   2. x(n) = 4x(n/4) + 2n
2. x(n/4) = 2x(n/8) + n/4
   1. x(n) = 4(2x(n/8) + n/4) + 2n
   2. x(n) = 8x(n/8) + 3n
3. x(n) = 2^k\*x(n/(2^k)) + kn
4. 1 = n/2^k
   1. 2^k = n
   2. k = lg(n)
5. x(n) = n + n\*lg(n)

## brute force - check all possible solutions

generate all pathagrean triplets

```c++
// a^2 + b^2 = c^2
```

## convex hull problem

A set of points (finite or infinite) in a plane is called convex if for any 2 points p and q in the set, the entire line segment with end points p and q belongs to the set.

The convex hull of a set S of points is the smallex convex set containing S.

so you have a cloud of points and you need to find the perimeter. you can solve this by choosing a line segment and checking if all other points are on one side of the segment. if they are, then it is a perimeter line. otherwise it is an inner line.

this is not just n! or n^2, because you need to create pairs of lines, and compare. creating the lines would be C(n, 2), or $\frac{n!}{2! \cdot (n-2)!} = \frac{n(n-1)}{2}$ and for verifying takes on average $\frac{n}{2}$, for a total complexity of $\theta (n^{3})$. Gram's method uses first sorts it and then it is a linear complexity.
