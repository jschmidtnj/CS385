#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> brgc(int n) {
  if (n == 1) {
    vector<string> res;
    res.reserve(2);
    res.push_back("0");
    res.push_back("1");
    return res;
  }
  // this is not quite right because order is wrong
  vector<string> base = brgc(n - 1);
  vector<string> l1, l2;
  for (int i = 0; i < base.size(); i++) {
    l1.push_back('0' + base[i]);
    l2.push_back('1' + base[base.size() - i - 1]);
  }
  l1.insert(l1.end(), l2.begin(), l2.end());
  return l1;
}

int main() {
  vector<string> res = brgc(3);
  for (string elem : res) {
    cout << elem << ' ';
  }
  cout << endl;
}
