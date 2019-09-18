# recursiveRelations

## selection sort

```python
def selection_sort(L):
    n = len(L)
    for i in range(n-1):
        min_index = i
        for j in range(i + 1, n):
            if L[j] < L[min_index]:
                min_index = j
        if i != min_index:
            swap(L, i, min_index)
```

- n + n-1 + n-2 + ... = n(n-1)/2
- primary operator is <

recurrance relation - for recursive function calls

initial condition: x(0) = 0

- x(n) = 1*(n-1) + (n-1)
- 1 = the number of times a recursive call is made
- first n-1 is the size of the data being processed in the recursive call
- second n-1 is the amount of work performed in the function excluding any recursive calls

```python
def selection_sort_rec(L):
    min_index = 0
    for i in range(1, len(L)):
        if L[i] < L[min_index]:
            min_index = i
    if min_index != 0:
        swap(L, 0, min_index)
    selection_sort_rec(L[1:])
```

1. continued: replace n with n - 1
   1. x(n-1) = x(n-2) + (n-2)
   2. x(n) = x(n-2) + (n-2) + (n-1)
2. replace n with n-2
   1. x(n-2) = x(n-3) + (n-3)
   2. x(n) = x(n-3) + (n-3) + (n-2) + (n-1)
3. when you see a pattern, get the general form
   1. x(n) = x(n-i) + (n-i) + (n-i+1) + (n-i+2) + ... + (n-1)
4. use the initial condition
   1. n - i = 0; i = n
5. produce a closed form expression using one of the summation rules
   1. x(n) = x(n-n) + (n-n) + 1 + 2 + ... + (n-1)
   2. n(x) = n(n-1)/2

## nlogn recursive

recurrence relation

0. x(n) = x(n/2) + 1, x(1) = 1
   1. recursive call made 1 time
   2. n/2 is size of data
1. replace n with n/2
   1. x(n/2) = x(n/4) + 1
   2. x(n) = x(n/4) + 2
2. replace n with n/4
   1. x(n/4) = x(n/8) + 1
   2. x(n) = x(n/8) + 3
3. generalize
   1. x(n) = x(n/(2^k)) + l
4. n/(2^k) = 1
   1. n = 2^k
   2. k = lgn
5. x(n) = x(n/2^k) + k
   1. = x(n/n) + lgn
   2. = 1 + lgn

## solve for n=2^k

x(n) = x(n/2) + 1, x(1) = 1

0. x(2^k) = x(2^(k-1)) + 1
1. x(2^(k-1)) = x(2^(k-2)) + 1
   1. x(2^k) = x(2^(k-2)) + 2
2. x(2^k-2) = x(2^(k-3)) + 1
   1. x(2^k) = x(2^(k-3)) + 3
3. x(2^k) = x(2^(k-i)) + i
4. 2^(k-i) = 1
   1. set input for base case equal to base case:
   2. 2^(k-i) = 2^0
   3. k-i = 0
5. x(2^k) = x(2^(k-k)) + k
   1. x(2^k) = 1 + k
   2. x(n) = 1 + lg(n)

## towers of hanoi

  |   |   |
 --- --- ---
  A   B   C
move 64 discs from A to C in same order

x(n) = 2x(n-1) + 1, x(1) = 1

1. x(n-1) = 2x(n-2) + 1
   1. x(n) = 2(2x(n-2) + 1) + 1
   2. = 4x(n-2) + 3
2. x(n-2) = 2x(n-3) + 1
   1. x(n) = 4(2x(n-3) + 1) + 3
   2. = 8x(n-3) + 7
3. x(n) = 2^kx(n-k) + 2^k-1
4. n-k=1
   1. k=n-1
5. x(n) = 2^(n-1)x(n-(n-1)) + 2^(n-1)-1
   1. = 2^(n-1) + 2^(n-1) - 2
   2. = 2*2^(n-1) - 1
   3. = 2^n - 1
