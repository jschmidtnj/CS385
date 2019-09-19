#! /usr/bin/python3

n = 3
thesum = 0
for i in range(n + 1):
  thesum += i**2
print(thesum)
print(n*(n+1)/2*(2*n+1)/3)

def mystery_2(n):
  return int(n*(n+1)*(2*n+1)/6)
print(mystery_2(3))

n = 4
thesum = 0
for i in range(n + 1):
  thesum += i**3
print(thesum)
print((n*(n+1)/2)**2)

def iterative(n):
  if n is 1:
    return 1
  S = 0
  for i in range(1, n + 1):
      S += i ** 3
  return S
print(iterative(4))

# figure out 4
