# topological sorting

don't put your shoes on before your socks

- used in compiling and having dependencies added
- academic catalog with course requirements

![topological](./topological.jpg "Topological sorting")

## lomuto sorting

- partitions subarray by lomuto's algorithm using first element as pivot

```bash
p ← A[l]
s ← l
for i ← l + 1 to r do
  if A[i] < p
    s ← s + 1; swap(A[s], A[i])
  swap(A[l], A[s])
  return s
```

- p = 4
- 4 5 2 1 11 7 8
- 1 2 4 5 11 7 8
- this partitions to move everything less than 4 on the left and everything greater than or equal to 4 on the right
- Theta(n)

### quickselect

-> find the 5243th smallest number

```bash
# making a copy of the array each time - not good
s ← LomutoPartition(A[l..r]) //or another partition algorithm
if s = k − 1 return A[s]
else if s > l + k − 1 Quickselect(A[l..s − 1], k)
else Quickselect(A[s + 1..r], k − 1 − s)
```

- worst case - $T(n) = T(n - 1) + \theta(n)$
- = $T(n) = \exists \theta(n^{2})$
- best case - $T(n) = T(\frac{n}{2}) + \theta(n)$
  - a = 1, b = 2, f(n) = n => d = 1
  - $T(n) \exists \theta(n)$

## quicksort

```bash
# ALGORITHM Quicksort(A[l..r])
  # Sorts a subarray by quicksort
  # Input: Subarray of array A[0..n − 1], defined by its left and right indices l and r
  # Output: Subarray A[l..r] sorted in  nondecreasing order
  if l < r
    s ←Partition(A[l..r]) //s is a split position
    Quicksort(A[l..s − 1])
    Quicksort(A[s + 1..r])
```

- 4 5 2 1 11 7 8
- 1 2 (4) 5 11 7 8
  - left side:
  - (1) 2 4 5 11 7 8
  - 1 (2) 4 5 11 7 8
- 1 2 4 (5) 11 7 8
  - right side:
  - 1 2 4 5 (11) 7 8
  - 1 2 4 5 (8) 7 11
  - 1 2 4 5 7 8 11

- worst case: $T(n) = T(n - 1) + \theta(n)$
  - $T(n) \exists \theta(n^{2})$
- best case: $T(n) = 2 \cdot T(\frac{n}{2}) + \theta(n)$
  - a = 2, b = 2, f(n) = n => d = 1
  - $T(n) \exists \theta(n \cdot lg(n))$

## inversions

an inversion is a pair of numbers where the larger number precedes the smaller number in the array

5 4 1 3 2

- (5, 4), (5, 1), (5, 3), (5, 2)
- (4, 3), (4, 1), (4, 2)
- (3, 2)

- brute force is n(n-1)/2 (2 for loops)
- how do we get nlgn? with merge sort! (with a slight modification)
- $T(n) = 2 \cdot T(\frac{n}{2}) + \theta (n)$
  - a = 2, b = 2, f(n) = n => d = 1
  - $a = b^{d}$ $T(n) \exists \theta (n \codt lg(n))$
- can find number of inversions by adding (mid - L + 1) each iteration (after adding to array)

|         | mergesort                |
|---------|--------------------------|
| best    | $\theta (n \cdot lg(n))$ |
| worst   | $\theta (n \cdot lg(n))$ |
| average | $\theta (n \cdot lg(n))$ |

```bash
MERGESORT(A, lo, hi)
 1. if lo < hi then
 2.     mid = lo + (hi - lo) / 2
 3.     MERGESORT(A, lo, mid)
 4.     MERGESORT(A, mid+1, hi)
 5.     L = lo
 6.     H = mid + 1
 7.     for k <- lo to hi
 8.         do if L <= mid and (H > hi or A[L] <= A[H])
 9.             then scratch[k] = A[L]
1.                   L <- L + 1
2.              else scratch[k] = A[H]
3.                   H <- H + 1
4.      for k <- lo to hi
5.          do A[k] <- scratch[k]
```

## counting sort

- this is Theta(n)
  - this is good for small numbers (because array needs to be huge)
  - what about using a map? it doesn't work
- [7 3 1 4 7 6 10 9 4]
- [0 0 0 0 0 0 0 0 0 0 0 ]
-  0 1 2 3 4 5 6 7 8 9 10
- [0 1 0 1 2 0 1 2 0 1 1 ]
- [1 3 4 4 6 7 7 9 10]

## bucket sort

- use this with uniform distribution of numbers
- Theta(n)
- [0.2, 0.3, 3.14, 2.718, 6.9, 4.20]
- (0, 1) -> 0.2, 0.3
- (1, 2)
- (2, 3) -> 2.718
- (3, 4) -> 3.14
- (4, 5) -> 4.20
- (5, 6)
- (6, 7) -> 6.9

## stable sort

- if duplicates exist in the original array, their order with respect to one another must be preserved in the sorted array

## radix sort

- sort by digits:
- original:             sorted:
- 1234      2000  2000        2
- 2000        41     2       41
-   41         2  1234      762
-    2       762    41     1234
-  762      1234   762     2000
- Theta(d * n) -> Theta(n)
  - d is number of digits
  - you should use base2 to make it fast
