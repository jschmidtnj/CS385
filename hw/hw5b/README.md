# anagram finder

- takes in a dictionary of words, and finds the anagrams
- one approach uses prime numbers, assigning each number to a prime number and then sorting based off of that - should be O(n)
- this works for up to 9 characters with unsigned long long
- another is to just use a dictionary for the sorted letters
- this works for more characters so it's the best way to go

## benchmarking

- benchmark with `sudo chrt -f 99 perf stat -ddd ./anagramfinder dictionary.txt`
- could also use `time ./anagramfinder dictionary.txt`, but this is not very accurate
