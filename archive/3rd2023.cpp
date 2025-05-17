#include <iostream>
using namespace std;

class Q {
protected:
    int dataq;
public: 
    Q(): dataq(0) {}
    Q(int _d): dataq(_d) {throw "Q";}
    int get() {return dataq;}
};
class P: public Q {
protected:
    int datap;
public:

    P() {datap=1;}
    P(int _p): datap(_p) {throw datap;}
    int get() {return datap;}
};
int main() {
    try {
        Q qq;
        cout <<qq.get();
        P ss;
        cout << ss.get();
        P pp(1);
        cout <<pp.get();
        P rr(2);
        throw rr.datap;
        cout <<rr.get();
    }
    catch (const char *a) {cout <<a;}
    catch (const int i) {cout <<i ;}
}