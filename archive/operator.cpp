#include <iostream>
using namespace std;
class Fraction {
    public:
    Fraction(int num, int den){
        this->num = num;
        this->den = den;
    }
    Fraction& operator++()
    {
    num += den; return *this;
    }
    Fraction operator++(int)
    {
    num += den;
    Fraction temp(num, den);
    return temp; 
    }

    void print(){
        cout << num << "/" << den << endl;
    } 
    private:
        int num;
        int den; 
        };

int main() {
Fraction a(1,2);
Fraction c;
cout << "a is ";
a.print();
cout << endl;
cout << "Prefix Increment" << endl; c = ++a;
cout << "c is ";
c.print();
cout << "a is ";
a.print();
cout << endl;
cout << "Postfix Increment" << endl; c = a++;
cout << "c is ";
c.print();
cout << "a is "; a.print();
return 0;
}