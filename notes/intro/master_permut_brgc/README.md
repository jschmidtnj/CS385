# Master Theorem

- $T(n) = a \cdot T(\frac{n}{b}) + f(n)$
  - a = num times the recursive call made in single function exec
  - b = constant factor by which the input size is divided
  - f(n) -> d = amount of work performed in the function excluding any recursive calls
- if $a < b^{d}$, $T(n) \exists \theta (n^{d})$
- if $a = b^{d}$, $T(n) \exists \theta (n^{d} \cdot log_{b} (n))$
- if $a > b^{d}$, $T(n) \exists \theta (n^{log_{b} (a)})$

the theorem only works for divide and conquer

for decrease and conquer (subtracting in recursive call), use backwards substitution

## lexicographic permutations

- dog -> sort -> dgo
- input is positive integer n
- output is list of all permutations of 1, ..., n in lexicographic order
- initialize first with 12 ... n
- while last permutation has 2 consecutive elements in increasing order
  - i = first index where 2 elements are in increasing order
  - j = largest index j where a[i] > a[j]
  - swap ai and aj
  - reverse order of elements from i+1 to n
  - add new permutation to list
- n! outputs, runtime is Theta(n*n!)
- balloon = 7!/(2!2!) permutations

## BRGC - generates the binary reflected gray code of order n

- BRGC(3)
  - BRGC(2)
    - BRGC(1) -> ['0', '1']
  - L1 = ['0', '1'] -> ['00', '01']
  - L2 = ['1', '0'] -> ['11', '10']
  - L1 = ['00', '01', '11', '10']
- L1 = ['00', '01', '11', '10'] -> ['000', '001', '011', '010']
- L2 = ['10', '11', '01', '00'] -> ['110', '111', '101', '100']
- L1 = ['000', '001', '010', '011', '100', 101', '110', '111']

time complexity: $T(n) = 1 \cdot T(n - 1) + \theta(2^{n})$

0. $T(n-1) = T(n-2) + 2^{n  - 1}$
1. $T(n) = T(n-2) + 2^{n-1} + 2^{n}$
2. $T(n) = T(n-3) + 2^{n-2} + 2^{n-1} + 2^{n}$
3. $T(n) = T(n-k) + 2^{n-k+1} + 2^{n-k-2} + ... + 2^{n}$
4. $T(1) = 2$ $n-k=1$ $n - 1$
5. $T(n) = T(n-(n-1)) + 2^{n-(n-1)+1} + 2^{n-(n-1)+2} + 2^{n}$
   1. $= 2^{1} + 2^{2} + 2^{3} + ... + 2^{n}$
   2. $T(n) = 2^{n+1} - 2$
