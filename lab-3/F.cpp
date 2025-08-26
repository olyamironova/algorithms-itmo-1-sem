#include <iostream>

struct Node {
    Node* prev = nullptr;
    int value;
};

struct Stack {
    Node* head = nullptr;
    void push(int value){
        Node* element = new Node;
        element->value = value;

        if(head == nullptr){
            head = element;
        } else {
            element->prev = head;
            head = element;
        }
    }

    void pop(){

        if(head->prev != nullptr){
            Node* tmp = head->prev;
            delete(head);
            head = tmp;

        } else {
            delete(head);
            head = nullptr;
        }
    }

    int top(){
        return head->value;
    }

    bool empty(){
        return head == nullptr;
    }
};

int main() {
    long long n;
    std::cin >> n;
    long long a[n];
    for (long long j = 0; j < n; j++) {
        std::cin >> a[j];
    }
    long long result[n];
    Stack stack;
    for (long long i = n - 1; i >= 0; i--) {
        while ((!(stack.empty())) && (a[stack.top()] <= a[i])) {
            stack.pop();
        }
        if (stack.empty()) {
            result[i] = -1;
        } else {
            result[i] = stack.top() - i;
        }
        stack.push(i);
    }
    for (long long i = 0; i < n; i++) {
        std::cout << result[i] << " ";
    }
}