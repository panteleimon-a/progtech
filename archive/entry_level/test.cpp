#include <iostream> 
using namespace std;
class BaseClass { 
    int x;
public:
    void setx(int n) {
        x = n; 
        }
    void showx() { cout << x;
    }
};
class DerivedClass : private BaseClass { 
    int y;
public:
    void setxy(int n, int m) {
        setx(n);
        y = m; 
        }
    void showxy(){ showx();
    cout << y << '\n';
        }
};

int main() { 
    DerivedClass ob; 
    ob.setxy(10, 20); 
    ob.showxy();
}