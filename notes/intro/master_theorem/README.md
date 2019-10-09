# Master Theorem

- $T(n) = a \cdot T(\frac{n}{b}) + f(n)$
  - a = num times the recursive call made in single function exec
  - b = constant factor by which the input size is divided
  - f(n) = amount of work performed in the function excluding any recursive calls
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
