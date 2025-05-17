#include <stdio.h>
#include <iostream>
using namespace std;
#include <stdlib.h>

class sq{
protected: 
    double n,s;
    void upd(){s=n*n;}
public:
    sq(): n(0), s(0){}
    sq(double x): n(x) {upd();}
    void set(double d) { n=d; upd();}
    double N() {return n;}
    double S() {return s;}
};

class cb:public sq{
protected:
    double c;
    void upd() {n=n*n; c=s*n;}
public:
    cb(): c(0){}
    cb(double x): sq(x) {c=n*n*n;}
    double C() {return c;}
};

int main(){
    cb *myc = new cb(2);
    sq *mys = myc;
    cout << mys->N()<<" "<<mys->S()<< " " << myc->C()<< " ";
    myc->set(3);
    cout << myc->N()<<" "<<myc->S()<< " " << myc->C()<< " ";
}