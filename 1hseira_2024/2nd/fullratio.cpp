// #ifndef __FULLRATIO_HPP__
// #define __FULLRATIO_HPP__
#include <iostream>
using namespace std;

class rational {
public:
    rational (int n, int d){ nom=n; den=d;};
    friend rational operator + (const rational &x, const rational &y){
        rational temp(1,1);
        temp.nom= x.nom*y.den+x.den*y.nom; 
        temp.den= x.den*y.den; 
        return temp;};
    friend rational operator - (const rational &x, const rational &y){
        rational temp(1,1);
        temp.nom= x.nom*y.den-x.den*y.nom; 
        temp.den= x.den*y.den; 
        return temp;};
    friend rational operator * (const rational &x, const rational &y){
        rational temp(1,1);
        temp.nom=x.nom*y.nom; 
        temp.den= x.den*y.den; 
        return temp;};
    friend rational operator / (const rational &x, const rational &y){
        rational temp(1,1);
        temp.nom=x.nom*y.den;
        temp.den=x.den*y.nom;
        return temp;};

    friend std::ostream & operator << (std::ostream &out, const rational &x){
        rational temp(1,1);
        int gcd = rational::gcd(x.nom,x.den);
        // rationals are printed simplified
        temp.nom=x.nom/gcd; 
        temp.den=x.den/gcd; 
        out<<temp.nom<<"/"<<temp.den;
        return out;
    };

private:
    int nom, den;
    static int gcd (int a, int b){     
        int result = min(a, b);
        while (result > 0) {
            if (a % result == 0 && b % result == 0) {
                break;
            }
            result--;
        };
    return result;
    };
};

int main() {
    rational a(1, 2);
    rational b(3, 4);
    rational c(5, 6);
    cout << a + b - c << endl;
    cout << a << " should still be 1/2" << endl;
    return 0;
};
//#endif    
