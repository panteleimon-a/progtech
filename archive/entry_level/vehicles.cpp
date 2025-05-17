#include <iostream>
using namespace std;

class vehicle {
    int wheels;
    float weight; 
public:
    virtual void message(void) { 
        cout << "Vehicle message\n";
    }
    };
    
class car : public vehicle {
    int passenger_load;
public:
    void message(void) {
    cout << "Car message\n";
        }
    };

class truck : public vehicle { 
    int passenger_load; 
    float payload;
public:
    int passengers(void) {
        return passenger_load;
        }
    };

class boat : public vehicle {
    int passenger_load;
public:
    int passengers(void) {
            return passenger_load; 
            }
    void message(void){
            cout << "Boat message\n";
            }
    };
int main() {
    vehicle *unicycle; 
    unicycle = new vehicle; 
    unicycle->message(); 
    delete unicycle;
    unicycle = new car; 
    unicycle->message(); 
    delete unicycle;
    unicycle = new truck; 
    unicycle->message(); 
    unicycle = new boat; 
    unicycle->message(); 
    delete unicycle; 
    return 0; }