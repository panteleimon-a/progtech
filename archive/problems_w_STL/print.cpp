#include <vector>
#include <list>
#include <iostream>
using namespace std;

template <typename C> 

void print(C &c) {
for (auto &x : c) cout << x << endl; 
}

int main() {
vector<int> v;
for (int i = 1; i <= 5; ++i) v.push_back(i); print(v); // print the vector -- C = vector<int> 
list<int> l;
for (int i = 1; i <= 5; ++i) l.push_back(i); print(l); // print the list -- C = list<int>
}