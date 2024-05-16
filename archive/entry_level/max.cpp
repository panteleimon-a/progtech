#include <iostream>
using namespace std;
template <class T, class U>
// now I am able to give different types of inputs
T GetMax (T a, U b) {
T result;
result = (a>b)? a : b; return (result);
}
int main () {
int i=5, j=6, k; long l=10, m=5, n;
k=GetMax(i,k); n=GetMax(l,m); cout << k << endl; cout << n << endl; return 0;
}
