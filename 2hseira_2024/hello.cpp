#include <iostream>
using namespace std;
int gcd(int x, int y) {
  while (x > 0 && y > 0)
    if (x > y) x %= y; else y %= x;
  return x + y;
}

int main() {
  cout << "Give me two numbers: ";
  int a, b;
  cin >> a >> b;
  cout << "GCD(" << a << ", " << b<< ") = " << gcd(a, b) << endl;
  cout << a << "%/2="<<a%2;
}