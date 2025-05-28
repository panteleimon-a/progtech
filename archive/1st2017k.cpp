#include <iostream>
using namespace std;

class vehicle {
        int wheels; 
        float weight;
    public:
        virtual void print(){
            cout << "Vehicle\n" << endl;
        }
    };

class boat : public vehicle {
        float passenger_load;
        float length;
    public:
        int passenger() {
            return passenger_load;
        }
        virtual void print() override{
            cout << "Boat\n" << endl;
        }
    };

class car : public vehicle { 
        int passengers;
        float length;
    public:
        int passenger() {
            return passengers;
        }
        virtual void print() {
            cout << "Car\n" << endl;
        }
    };

class truck : public vehicle {
        int passengers;
        float length;
    public:
        int passenger() {
            return passengers;
        }
    };

int main() {
    // Using pointer for v1 (as in your original code)
    vehicle *v1;
    v1 = new vehicle();
    v1->print();
    delete v1;  // Add this to avoid memory leak
    v1= new car();
    v1->print();
    delete v1;  // Add this to avoid memory leak
    v1 = new truck();
    v1->print();
    delete v1;  // Add this to avoid memory leak
    v1 = new boat();
    v1->print();
    delete v1;  // Add this to avoid memory leak
}
