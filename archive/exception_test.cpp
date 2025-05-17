#include <iostream>
using namespace std;

class unreal_rectangle : public exception {
    public:
    const char* what(){
        return "Invalid rectangle parameters";
    };
};
class Rectangle {
    public:
    Rectangle(int a, int b){
    height=a;
    base=b;};
    void const area(){ 
        cout<<"Area in cubic meters: "<<height*base<<endl;};
    private:
    int base, height;
};

int main(){
    int a=-1,b=1;
    Rectangle R(a,b);
    try{
        if (a<0 || b<0) throw unreal_rectangle();
        R.area();
    }
    catch(unreal_rectangle &e){
    cout<<"Tin gamisame: "<<e.what();
    };
};