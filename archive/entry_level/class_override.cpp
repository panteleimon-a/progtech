#include <iostream>
using namespace std;
template <class T>
T std::pair (T first, T second) { 
    value1=first; 
    value2=second;
}
//T retval;
//retval = value1>value2? value1 : value2; return retval;
//}
int main () {
    int myobject;
    myobject= pair(100, 75); 
    cout << myobject.getmax(); return 0;
}