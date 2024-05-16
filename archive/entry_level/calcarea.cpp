// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

class Shape {
    private:
        float area; 
    public:
        float calculateArea(void);
};

class Triangle: public Shape{ 
    private:
        float area; 
        float height; 
        float base;
    public:
        // member functions
        void calculateArea() {
            float result;
            result = (base*height)/2;
            putArea(result);
        }
        void putHeight(float value) { 
            height = value;
        }
        void putArea(float value) { 
            area = value;
        }
        void putBase(float value) {
            base = value;
        }
        float getArea() {
            return area;
        }
        float getHeight() {
            return height;
        }


};

class Circle: public Shape{ 
    private:
        float area; 
        float height; 
        float base;
        float radius;
    public:
        void putArea(float value) { 
            area = value;
        }
        void calculateArea(){
            float result;
            result = 3.14*radius*radius;
            putArea(result);
        }
        // member functions
        void putRadius(float value) { 
            radius = value;
        }
        float getArea() { 
            return area;
        }
    };

int main() { 
    typedef Triangle* PointerToTriangle;
    PointerToTriangle aTriangle;
//ή Triangle *aTriangle
    Circle aCircle;
    float circleArea, triangleArea;
    

    aTriangle = new Triangle;
    
    aTriangle->putHeight(10.0); 
    aTriangle->putBase(2.0);
    
    aCircle.putRadius(10.0);
    aTriangle->calculateArea(); 
    circleArea = aCircle.getArea();
    triangleArea = aTriangle -> getArea();
    cout << "The area of the Triangle is " << triangleArea << endl;
    cout << "The area of the Circle is " << circleArea << endl;
    return 0;
};