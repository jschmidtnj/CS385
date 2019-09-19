#include <iostream>

using namespace std;

class Lab3
{
private:
public:
  Lab3();
  int mystery1(int a, int b);
  void mystery2(int values[], int i, int j);
  int mystery3(int x, int y);
};

Lab3::Lab3() {}

int Lab3::mystery1(int a, int b)
{
  int c = a - b,
      d = (c >> 7) & 1,
      mystery = a - c * d;
  return mystery;
}

void Lab3::mystery2(int values[], int i, int j)
{
  values[i] = values[i] ^ values[j];
  values[j] = values[i] ^ values[j];
  values[i] = values[i] ^ values[j];
}

int Lab3::mystery3(int x, int y)
{
  int s, c;
  s = x ^ y;
  c = x & y;
  while (c != 0)
  {
    c = c << 1;
    x = s;
    y = c;
    s = x ^ y;
    c = x & y;
  }
  return s;
}

int main(int argc, char *const argv[])
{
  Lab3 thelab = Lab3();
  cout << thelab.mystery1(3, 7) << '\n';
  cout << thelab.mystery1(8, 7) << '\n';
  int values[4] = {1, 2, 3, 4};
  thelab.mystery2(values, 0, 3);
  for (int i = 0; i < 4; i++)
    cout << values[i] << ", ";
  cout << endl;
  int values2[4] = {1, 2, 3, 4};
  thelab.mystery2(values2, 1, 2);
  for (int i = 0; i < 4; i++)
    cout << values2[i] << ", ";
  cout << endl;
  cout << thelab.mystery3(5, 7) << '\n';
  cout << thelab.mystery3(2, 8) << '\n';
}
