#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

// command line args
// ./gcd 24 52
// argc = integer argument count
// argv = argument values as char arrays
// argv -> [0 -> [., ., g, c, d, \0], 1, 2]
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

    cout << "m is " << m << endl;
    cout << "n is " << n << endl;
    cout << "max(" << m << ", " << n << ") is " << max(m, n) << endl;
    return 0;
}
