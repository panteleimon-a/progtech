// #ifndef CONTEST
#include <iostream>
using namespace std;
// #endif

class rational {
public:
rational (int n, int d){ nom=n; den=d;};

 rational add (rational r){ nom= nom*r.den+den*r.nom; den*=r.den; return rational(nom,den);};
 rational sub (rational r){ nom= nom*r.den-den*r.nom; den*= r.den; return rational(nom,den);};
 rational mul (rational r){ nom *=r.nom; den*= den*r.den; return rational(nom,den);};
 rational div (rational r){ nom*=r.den ;den*=r.nom; return rational(nom,den);};

 void print () { 
    int gcd = rational::gcd(nom,den);
    // rationals are printed simplified
    nom/=gcd; 
    den/=gcd; 
    cout << nom << "/" << den << endl;
    };

private:
    int nom, den; // nominator, denominator
    // gcd function needed for rational number simplification
    static int gcd (int a, int b){     
        int result = min(a, b);
        while (result > 0) {
            if (a % result == 0 && b % result == 0) {
                break;
            }
            result--;
        }
    return result;
};
 };