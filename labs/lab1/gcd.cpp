/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Joshua Schmidt
 * Version : 1.0
 * Date    : August 29, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>

using namespace std;

// do the same algorithm as recursive function but iterative
int gcd_iterative(int m, int n) {
  int temp;
  while (m != 0) {
    temp = m;
    m = n % m;
    n = temp;
  }
  return abs(n);
}

// algorithm is to take mod of n and m, and keep passing
// in m as n to keep modding by remainder
// make sure it's a positive number
int gcd_recursive(int m, int n) {
  if (m == 0)
    return abs(n);
  return gcd_recursive(n % m, m);
}

// use same code for number input
// then make sure output is the same
int main(int argc, char* const argv[]) {
  int m, n;
  istringstream iss;
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
        << endl;
    return 1;
  }
  iss.str(argv[1]);
  if ( !(iss >> m) ) {
    cerr << "Error: The first argument is not a valid integer."
        << endl;
    return 1;
  }
  iss.clear(); // clear the error code
  iss.str(argv[2]);
  if ( !(iss >> n) ) {
    cerr << "Error: The second argument is not a valid integer."
        << endl;
    return 1;
  }
  cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m, n) << endl;
  cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m, n) << endl;
}
