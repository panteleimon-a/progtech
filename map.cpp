#include <iostream> 
#include <map>
#include<bits/stdc++.h> 
using namespace std;
 
int main(){
    map<int, int> m;
 
    m[1] = 2; // Insertion by indexing
 
    // Direct pair insertion
    m.insert({ 4, 5 });
 
    // Insertion of pair by make_pair
    m.insert(make_pair(8, 5));
 
    cout << "Elements in map:\n";
    for (auto it : m)
        cout << "[ " << it.first << ", "
             << it.second << "]\n"; // Sorted
 
    return 0;
}