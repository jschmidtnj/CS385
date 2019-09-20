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
