// C++ program to demonstrate function overriding

#include <iostream>
using namespace std;

class Base {
   public:
    virtual void print() {
        cout << "Base Function" << endl;
    }
};

class Derived : public Base {
   public:
    void print() override {
        cout << "Derived Function" << endl;
    }
};

class DerivedSq : public Derived {
   public:
    void print() override {
        cout << "DerivedSq Function" << endl;
    }
};

int main() {
    Base* b1 = new Derived;
    Base* b2 = new DerivedSq;
    b1->print();
    b2->print();
    return 0;
}