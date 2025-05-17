#include <iostream>
using namespace std;

template <typename T>
class stack {
public:
    stack (int size): s(size), top(-1) {
            stack_arr = new T[s]; // Allocate memory for the stack
        }
    // used for copying stack
    stack (const stack &s){ stack_arr = s.stack_arr; }
    ~stack () { delete[] stack_arr;} // Clean up memory when the stack object is destroyed
    const stack & operator = (const stack &s) { 
        if (this != &s) { // Check for self-assignment
            stack_arr = s.stack_arr;
        } 
        return *this;
    } 
    int getTop() { return this->top; }
    int getSize() { return this->s; }
    bool empty () { return (top == -1);}
    void push (const T &x) {
        if (top >= s - 1) {
            std::cout << "Stack is full. Cannot push.\n";
            return;
        }
        top++;
        stack_arr[top] = x;
        cout << "Pushed: " << x << endl;
    }
    T pop () {
        if (top < 0) {
            std::cout << "Stack is empty. Cannot pop.\n";
            return -1; // Return a default value
        }
        int popped_element = stack_arr[top];
        top--;
        cout << "Popped: " << popped_element << endl;
        return popped_element;
    }

    friend ostream & operator << (ostream &out, const stack &s) {
        stack temp_stack=s;
        int temp=0;
        out << "Stack contents: [";
        while (!temp_stack.empty() && temp<=temp_stack.top) {
            out << temp_stack.stack_arr[temp++];
            if (!temp_stack.empty()) {
                out << ", ";
            }
        }
        out << "]";
        return out;
    }

private:
    int s; // Size of the stack
    int top;
    T* stack_arr; // Dynamic array to store stack elements
    
};


// #ifndef CONTEST
int main () {
    // let's play with integers...
    stack<int> s(10);
    cout << "s is empty: " << s << endl;
    s.push(42);
    cout << "s has one element: " << s << endl;
    s.push(17);
    s.push(34);
    cout << "s has more elements: " << s << endl;
    cout << "How many? " << s.getSize() << endl;
    stack<int> t(5);
    t.push(7);
    cout << "t: " << t << endl;
    t = s;
    cout << "popping from s: " << s.pop() << endl;
    s.push(8);
    stack<int> a(s);
    t.push(99);
    a.push(77);
    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "a: " << a << endl;
    // now with doubles...
    stack<double> c(4);
    c.push(3.14);
    c.push(1.414);
    cout << "c contains doubles " << c << endl;
    // and with characters...
    stack<char> k(4);
    k.push('$');
    cout << "k contains a character " << k << endl;
}
//#endif
