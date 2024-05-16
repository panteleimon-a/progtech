#include <iostream>
using namespace std;
 
// Base Class
class BaseClass {
public:
    int var_base;
 
    // Function to display the base
    // class members
    void display()
    {
        cout << "Displaying Base class"
             << " Fuck you, here is your proof " << var_base << endl;
    }
};
 
// Class derived from the Base Class
class DerivedClass : public BaseClass {
public:
    int var_derived;
 
    // Function to display the base
    // and derived class members
    void display()
    {
        cout << "Again fuck you "
             << "variable var_base: " << var_base << endl;
        cout << "Displaying Derived "
             << " class variable var_derived: "
             << var_derived << endl;
    }
};
 
// Driver Code
int main()
{
    // Pointer to base class
    BaseClass* base_class_pointer;
    BaseClass obj_base;
    DerivedClass* derived_class_pointer;
    DerivedClass obj_derived;
 
    // Pointing to derived class
    base_class_pointer = &obj_derived;
    base_class_pointer->var_base = 34;
    // Calling base class member function
    base_class_pointer->display();
    // Derived class pointer
    derived_class_pointer->var_derived = 777;
    derived_class_pointer->var_base= 34;
    // Calls derived class
    derived_class_pointer->display();
    derived_class_pointer= &obj_base; // a child class pointer cannot point to base
    derived_class_pointer->display();
 
    return 0;
}