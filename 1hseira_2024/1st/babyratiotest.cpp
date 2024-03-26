#include <iostream>
#include "babyratio.hpp"

using namespace std;


// 1. convert babyratio.cpp to babyratio.hpp and remove "main"
// 2. compile

int main() {
    rational a(1, 2);
    rational b(3, 4);
    rational c(5, 6);
    a.print();
    cout << endl;
    a.add(b).sub(c).print();
    cout << " should be 20/48" << endl;
    return 0;}