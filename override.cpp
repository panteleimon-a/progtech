// C++ program to demonstrate function overriding

#include <iostream>
using namespace std;

class Base {
   public:
    void print() {
        cout << "Base Function" << endl;
    }
};

class Derived : public Base {
   public:
    virtual void print() {
        cout << "Derived Function" << endl;
    }
};

class DerivedSq : public Derived {
   public:
    void print() {
        cout << "DerivedSq Function" << endl;
    }
};

int main() {
    DerivedSq derived1;
    derived1.Derived::print();
    return 0;
}