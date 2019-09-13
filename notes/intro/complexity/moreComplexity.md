# complexity continued

## an example

assume f(n) is measured in microseconds. What is the largest n you can solve for in time t?
t = 1 hour = 10^6 microseconds/s * 60s/min * 60min/hr = 3.6*10^9 microseconds

2^(log2n) = 2^(3.6*10^9)
        n = 2^(3.6*10^9)

sqrt(n)^2 = (3.6*10^9)^2
        n = (3.6*10^9)^2 = 1.296*10^19

nlgn = 3.6*10^9
   n = 133378058
-> can use binary search to do this - just guess and check to find the answer

## more math

lim (n -> inf) t(n) / g(n) = { 0 => t(n) has a smaller order of growth than g(n)
                               c =>            same
                               inf =>          larger }

L'Hopital's Rule
lim (n -> inf) t(n) / g(n) = lim (n -> inf) t\`(n) / g\`(n)

Sterling's approximation
n ~ sqrt(2*pi*n)*(n/e)^n for large values of n

ex. compare log2(n) and sqrt(n)
`$$\lim_{x\to\infty} \frac{log_2(n)}{\sqrt{n}}$$ = $$\lim_{x\to\infty} \frac{\frac{1}{log_2(n)}}{\frac{1}{2 \cdot \sqrt{n}}}$$ = 0`

use equation editor in future if possible found [here](https://www.codecogs.com/latex/eqneditor.php)

![equation](https://latex.codecogs.com/svg.latex?%24%24%5Clim_%7Bx%5Cto%5Cinfty%7D%20%5Cfrac%7Blog_2%28n%29%7D%7B%5Csqrt%7Bn%7D%7D%24%24%20%3D%20%24%24%5Clim_%7Bx%5Cto%5Cinfty%7D%20%5Cfrac%7B%5Cfrac%7B1%7D%7Blog_2%28n%29%7D%7D%7B%5Cfrac%7B1%7D%7B2%20%5Ccdot%20%5Csqrt%7Bn%7D%7D%7D%24%24%20%3D%200)

ex 3. compare n! and 2^n
use Sterling's = infinity

Theorem: If t1(n) E O(g1(n)) and t2(n) E O(g2(n)), then t1(n) + t2(n) E O(mat{g1(n), g2(n)})

t1 = 3n^2 + 21 E O(n^2)
t2 = 13n + 90 E O(n)
3n^2 + 13n + 90 E O(n^2)

just use a c1, c2, n and plug it in to prove it
