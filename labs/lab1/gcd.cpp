#include <iostream>
#include <sstream>

using namespace std;

int gcd_iterative(int m, int n) {
  int temp;
  while (m != 0) {
    temp = m;
    m = n % m;
    n = temp;
  }
  return n < 0 ? -n : n;
}

int gcd_recursive(int m, int n) {
  if (m == 0)
    return n < 0 ? -n : n;
  return gcd_recursive(n % m, m);
}

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
