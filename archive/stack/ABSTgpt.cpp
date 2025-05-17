#include <iostream>

class Stack {
private:
    int* stack_arr; // Dynamic array to store stack elements
    int top;
    int size; // Size of the stack

public:
    Stack(int n) : size(n), top(-1) {
        stack_arr = new int[size]; // Allocate memory for the stack
    }

    ~Stack() {
        delete[] stack_arr; // Clean up memory when the stack object is destroyed
    }

    void push(int data) {
        if (top >= size - 1) {
            std::cout << "Stack is full. Cannot push.\n";
            return;
        }
        top++;
        stack_arr[top] = data;
        std::cout << "Pushed: " << data << std::endl;
    }

    int pop() {
        if (top < 0) {
            std::cout << "Stack is empty. Cannot pop.\n";
            return -1; // Return a default value
        }
        int popped_element = stack_arr[top];
        top--;
        std::cout << "Popped: " << popped_element << std::endl;
        return popped_element;
    }

    int topElement() {
        if (top < 0) {
            std::cout << "Stack is empty.\n";
            return -1; // Return a default value
        }
        return stack_arr[top];
    }

    bool isEmpty() {
        return (top == -1);
    }
};

int main() {
    Stack myStack(5); // Create a stack with size 5

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    myStack.pop();

    int topElement = myStack.topElement();
    if (topElement != -1) {
        std::cout << "Top element: " << topElement << std::endl;
    }

    return 0;
}
