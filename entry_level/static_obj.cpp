// static members in classes
#include <iostream>
using namespace std;


class CTest {
    public:
        int n=0;
    CTest () { n++; }; 
    ~CTest () { n--; };
};

int main () { 
    CTest a;
    CTest b[5];
    CTest * c = new CTest;
    cout << a.n << endl; 
    delete c;
    cout << a.n << endl; return 0;
};