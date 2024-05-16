#include <iostream>
using namespace std;

class A{
public:
    A() {cout << "A";}
    ~A() {cout << "a";}
    void o() {cout <<"@";}
};

class B: public A{
public:
    B() {cout <<"B";}
    ~B() {cout<<"b";}
    void o() {cout<<"#";};
};

int main(){
    B b;
    A *c = &b;
    c->o();
    b.o();
}