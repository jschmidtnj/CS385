/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Joshua Schmidt
 * Version     : 1.0
 * Date        : 9/26/2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
  // returns true if all characters in string are lowercase
  // letters in the English alphabet; false otherwise.
  for (const char currentChar: s)
    if (currentChar < 'a' || currentChar > 'z')
      return false;
  return true;
}

bool all_unique_letters(const string &s) {
  // returns true if all letters in string are unique, that is
  // no duplicates are found; false otherwise.
  // You may use only a single int for storage and work with bitwise
  // and bitshifting operators.
  // No credit will be given for other solutions.
  int vector = 0;
  unsigned int current;
  for (const char currentChar: s) {
    current = 1 << (currentChar - 'a');
    if (current & vector)
      return false;
    else
      vector |= current;
  }
  return true;
}

int main(int argc, char * const argv[]) {
  // reads and parses command line arguments.
  // Calls other functions to produce correct output.
  if (argc != 2) {
    cerr << "Usage: ./unique <string>" << endl;
    return 1;
  }
  const string input = string(argv[1]);
  if (!is_all_lowercase(input)) {
    cerr << "Error: String must contain only lowercase letters." << endl;
    return 1;
  }
  if (!all_unique_letters(input))
    cout << "Duplicate letters found." << endl;
  else
    cout << "All letters are unique." << endl;
  const char test = 'c';
  cout << (test > 'a');
  cout << (test <'z');
}
