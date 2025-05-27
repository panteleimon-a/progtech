#include <iostream>
using namespace std;

class vehicle {
        int wheels; 
        float weight;
    public:
        vehicle(int w = 0, float wt = 0) : wheels(w), weight(wt) {}
        virtual void print() {
            cout << "Vehicle with " << wheels << " wheels and weight " << weight << endl;
        }
    };

class boat : public vehicle {
        float passenger_load;
        float length;
    public:
        boat(float pass = 0, float len = 0, int w = 0, float wt = 0) 
            : vehicle(w, wt), passenger_load(pass), length(len) {}
        int passenger(){
            return passenger_load;
        }
        void print() {
            cout << "Boat with " << this->passenger() << " passengers " << endl;
        }
    };

class car : public vehicle { 
        int passengers;
        float length;
    public:
        car(int pass = 0, float len = 0, int w = 4, float wt = 0)
            : vehicle(w, wt), passengers(pass), length(len) {}
        int passenger(){
            return passengers;
        }
        virtual void print()  {
            cout << "Car with " << this->passenger() << " passengers " << endl;
        }
    };

class truck : public car {
        int passengers;
        float length;
    public:
        truck(int pass = 0, float len = 0, int w = 6, float wt = 0)
            : car(pass, len, w, wt), passengers(pass), length(len) {}
        int passenger(){
            return passengers;
        }
    };

int main() {
    // Using pointer for v1 (as in your original code)
    vehicle *v1 = new vehicle(2, 100.5);
    v1->print();
    delete v1;  // Add this to avoid memory leak
    
    // Using objects directly (without pointers)
    car v2(4, 4.5);
    v2.print();
    
    boat v3(12, 25.5);
    v3.print();
    
    truck v4(2, 10.5);
    v4.print();  // This will call vehicle::print() unless you override it
    
    return 0;
}
