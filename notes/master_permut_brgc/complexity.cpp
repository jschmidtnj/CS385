#include <iostream>

using namespace std;

// cannot use it here b/c it is not dividing
int function0(int n) {
    int temp = 1;
    if (n <= 1) {
        return temp;
    }
    temp += function0(n - 1);
    return temp;
}

// a = 2, b = 2
// f(n) = theta(1) => n^0 => d = 0
// a _ b^d
// 2 >= 2^0
// T(n) E theta(n^log2(n)) = theta(n)
int function1(int n) {
    int temp = 1;
    if (n <= 1) {
        return temp;
    }
    temp += function1(n / 2);
    temp += function1(n / 2);
    return temp;
}

// a = 1
// b = 2
// f(n) = theta(n) => n^1 => d = 1
// 1 < 2^1
// T(n) E theta(n^1) = theta(n)

// n + n/2 + n/4 + ... + n/n = 2n
int function2(int n) {
    int temp = 0;
    if (n > 1) {
        for (int i = 1; i <= n; ++i) {
            ++temp;
        }
        temp += function2(n / 2);
    }
    return temp;
}

// a = 8 (in the for loop)
// b = 2
// f(n) = theta(n^3) -> d = 3
// 8 = 2^3
// T(n) E theta(n^3 lgn)
int function3(int n) {
    if (n <= 1) {
        return 0;
    }
    int temp = 0;
    for (int i = 1; i <= 8; ++i) {
        temp += function3(n / 2);
    }
    for (int i = 1, max = n * n * n; i <= max; ++i) {
        ++temp;
    }
    return temp;
}

// a = 2,
// b = 2
// f(n) = Theta(n) => d=1
// 2 = 2^1
// T(n) E theta(nlgn)
int function4(int n) {
    int temp = 1;
    for (int i = 1; i <= n; ++i) {
        ++temp;
    }
    temp += function1(n / 2);
    temp += function1(n / 2);
    return temp;
}

// x(n) = 4x(n/2) + n for all n > 1, x(1) = 1
// a = 4
// b = 2
// f(n) = Theta(n) => d = 1
// 4^1 > 2
// T(n) E Theta(n^(lg4))
// Theta(n^2)

int main() {
    cout << function0(16) << endl;
    cout << function1(16) << endl;
    cout << function2(16) << endl;
    cout << function3(16) << endl;
    cout << function4(16) << endl;
    cout << endl;
    cout << function0(64) << endl;
    cout << function1(64) << endl;
    cout << function2(64) << endl;
    cout << function3(64) << endl;
    cout << function4(64) << endl;
    return 0;
}
