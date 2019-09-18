# hw 2

4. consider algorithm:

n = [non negative number input]
S = 0
for i = 1 to n do
    S = S + i * i
return S

n = 3: 0 + 1 + 4 + 9 = 14

a. what does this algorithm compute? this algorithm computes the sum of all squared integers from 0 to n.  
b. What is its basic operation? S = S + i * i: This basic operation sets the current sum equal to the current sum + the square of the iterator.  
c. How many times is the basic operation executed? n times.  
d. What is the efficiency clas of this algorithm? θ(n)  
e. Suggest an improvement to the algorithm, or prove it cannot be improved. 1 + 2 + ... + n = n(n+1) / 2. 1^2 + 2^2 + ... + n^2 = (n(n+1)/2)((2n+1)/3)
