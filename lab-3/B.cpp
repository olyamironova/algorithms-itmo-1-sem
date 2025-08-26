#include <iostream>

struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    long long value;
};

struct Queue {
    Node* head = nullptr;
    Node* tail = nullptr;
    int CounterDelete = 0;
    void push(long long value) {
        Node* element = new Node;
        element->value = value;

        if(tail == nullptr && head == nullptr) {
            head = element;
            tail = element;
        } else {
            tail->next = element;
            tail->next->prev = element;
            tail = element;
        }
    }
    void pop() {
        Node* tmp = head->next;
        if (head->next != nullptr) {
            delete(head);
            head = tmp;
        } else {
            delete(head);
            head = nullptr;
            tail = nullptr;
        }
    }
    long long top() {
        return head->value;
    }
    bool empty() {
        return head == nullptr;
    }
    void print(){
        Node* pointer = head;
        while(!empty()){
            std::cin.tie(0);
            std::cout << pointer->value << '\n';
            pointer = pointer->next;
        }
    }
};

int main() {
    Queue GeneralQueue;
    Queue Deleted;
    long long CounterOfPeople;
    std::cin >> CounterOfPeople;
    char TypeOfOperation;
    long long People;
    int CounterDelete = 0;
    for (long long i = 0; i < CounterOfPeople; ++i) {
        std::cin >> TypeOfOperation;
        if (TypeOfOperation == '-') {
            CounterDelete ++;
        }
        else if (TypeOfOperation == '+') {
            std::cin >> People;
            GeneralQueue.push(People);
        }
    }
    while (CounterDelete > 0 && (!GeneralQueue.empty())) {
        std::cout << GeneralQueue.top() << '\n';
        GeneralQueue.pop();
        CounterDelete--;
    }
}