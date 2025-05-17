// #ifndef CONTEST
#include <iostream>
using namespace std;
// #endif
int main() {
    rational a(1, 2);
    rational b(3, 4);
    rational c(5, 6);
    a.print();
    cout << endl;
    a.add(b).sub(c).print();
    cout << " now should be 5/12 (simplified)" << endl;
    return 0;}


