# binary operations


## example - check uniqueness

a b c c
unsorted = O(n^2)
sorted = sorted algorithm + O(n)

dictionary is O(n), but there is overhead for hashing
array of booleans for ascii values - O(n), even smaller
how about just a 32 bit integer (26 characters in alphabet) - acts as an array of booleans in a number

## bit shifting

-> need bit shifting and bitwise operators
int a = 5; 0101
cout << (a << 2); // shifts a left by 2 => 010100
// prints out 20
// shift left 1 multiplies by 2

int b = 13;
cout << (b >> 1); // shifts b right by 2 => 1101 => 110 = 6
// shift right divides by 2

// 1101...1
// signed int -> when shifting right the number is filled in with a 1 on the left
// unsigned int -> fills in with 0
// no unsigned ints in java - use >>> to shift and add a 0

## bitwise operations

bitwize operators

and:
  5    0101
& 7   &0111
____  _____
       0101

or:
  5    0101
| 7   |0111
____  _____
       0111

xor:
  5    0101
^ 7   ^0111
____  _____
       0010

ternary (negation - does this for all 32 bits...):
~ 5    0101
____  _____
       1010

## back to the example

unsigned int char_setter = 1 << current_char - 'a'; // gets 0 for a, 1, for b, 10 for c, etc.
// bit shift to the left to add this to the int at that bit

unsigned int vector; // "array" of characters

unsigned int in_vector = char_setter & vector; // checks if it is in the vector
vector = vector | char_setter; // add the current char_setter into vectors
// this can technically be theta(1) because you can have 27 characters to get a duplicate
