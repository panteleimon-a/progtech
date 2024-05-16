#include <iostream>
#include <stack>

class MyStack {
private:
    std::stack<int> data; // Using std::stack as an example

public:
    void push(int value) {
        data.push(value);
    }

    int pop() {
        int top_value = data.top();
        data.pop();
        return top_value;
    }

    bool isEmpty() const {
        return data.empty();
    }

    // Overload the << operator
    friend std::ostream& operator<<(std::ostream& os, const MyStack& stack) {
        os << "Stack contents: [";
        std::stack<int> temp_stack = stack.data; // Create a copy for printing
        while (!temp_stack.empty()) {
            os << temp_stack.top();
            temp_stack.pop();
            if (!temp_stack.empty()) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

int main() {
    MyStack myStack;
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    std::cout << myStack << std::endl; // Print the stack

    myStack.pop();

    std::cout << myStack << std::endl; // Print the updated stack

    return 0;
}
