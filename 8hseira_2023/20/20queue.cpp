#include <iostream>
using namespace std;

// Define a node for the linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class queue {
public:
    queue (): front(nullptr), rear(nullptr) {}; /* κατασκευαστής: κατασκευάζει μία κενή ουρά */
    bool empty () const {
        return front == nullptr;
    }; /* ελέγχει αν η ουρά είναι κενή */

    void enqueue (int x){
        Node* newNode = new Node(x);
        if (empty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }; /* εισάγει ένα στοιχείο στην ουρά */
    int dequeue () {
        if (empty()) {
            std::cout << "Queue is empty. Cannot dequeue.\n";
            return -1; // Return a default value
        }
        Node* temp = front;
        int dequeuedValue = temp->data;
        front = front->next;
        delete temp;
        return dequeuedValue;
    }; /* αφαιρεί ένα στοιχείο από μια μη κενή ουρά */
    int peek (){
    if (!this->empty()) {
        return getHead();
    } else {
        std::cout << "Queue is empty. Cannot retrieve front element.\n";
        return -1; // Return a default value
    }
}; /* επιστρέφει (χωρίς να αφαιρεί) το πρώτο στοιχείο μιας μη κενής ουράς */
    int getHead() { return front->data; }
private:
    Node* front; // Pointer to the front (head) of the queue
    Node* rear;  // Pointer to the rear (tail) of the queue
};

int main() {
    queue myQueue;
    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);
    myQueue.enqueue(40);
    cout<<myQueue.peek()<<endl;
    return 0;
}
