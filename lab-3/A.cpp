#include <iostream>

struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    int value;
};

struct Stack {

    Node* head = nullptr;
    Node* tail = nullptr;

    void push(int value){
        Node* element = new Node;
        element->value = value;

        if(head == nullptr){
            head = element;
            tail = element;
        } else {
            head->next = element;

            element->prev = head;

            head = element;
        }

    }

    void pop(){

        if(head->prev != nullptr){

            Node* tmp = head->prev;
            tmp->next = nullptr;

            delete(head);

            head = tmp;

        } else {

            delete(head);
            head = nullptr;
            tail = nullptr;

        }

    }

    int top(){
        return head->value;
    }

    bool empty(){
        return head == nullptr;
    }

    void print(){
        Node* pointer = tail;
        while(pointer != nullptr){
            std::cin.tie(0);
            std::cout << pointer->value << '\n';
            pointer = pointer->next;
        }
    }
};

int main() {
    Stack chat;
    Stack deleted;
    int CountMessages;
    std::cin >> CountMessages;
    char TypeOfOperation;
    long long Message;
    for (int i = 0; i < CountMessages; ++i) {
        std::cin >> TypeOfOperation;
        if (TypeOfOperation == '-') {
            deleted.push(chat.top());
            chat.pop();
        } else if (TypeOfOperation == '+') {
            std::cin >> Message;
            chat.push(Message);
        }
    }
    deleted.print();
}