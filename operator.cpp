#include <iostream>
using namespace std;
class Fraction {
    public:
    Fraction(int num , int den){
        this->num = num;
        this->den = den;
    }
    
    Fraction& operator+=(const Fraction &rhs){
        this->num = rhs.den * this->num +this->den * rhs.num;
        this->den = this->den * rhs.den;
        return *this;
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
    Fraction c(1,1);
    cout << "a is ";
    a.print();
    cout << endl;
    cout << "c is ";
    c.print();
    cout << endl;
    c += a;
    cout << "c += a is ";
    c.print();
    return 0;
    }