#include <iostream>
using namespace std;
class A{
    public:
    void p1(){
        cout<<"g";p2();}
    virtual void p2(){
        cout<<"a";
    }
};
class B: public A{
    public:
    void p1(){cout << "t"; p2();}
    void p2() override {cout << "c";}
};

int main(){
    A *p=new A;
    B *q=new B;
    p->p1();
    q->p1();
    p=q;
    q->p2();
    q->p1();
}