#include <iostream>

struct Node {
    long long value;
    Node *next;
    Node *prev;

    Node(long long Value, Node *Next, Node *Prev) {
        value = Value;
        next = Next;
        prev = Prev;
    }
};

struct LinkedList{
    Node *head = nullptr;
    Node* tail = nullptr;

    long long pop_head() {
        if (head != nullptr) {
            long long v = head->value;
            if (head->next != nullptr) {
            Node* current = head->next;
            delete head;
            head = current;
            return v;
            } else {
                delete(head);
                head = nullptr;
                return v;
            }
        } else {
            return 0;
        }
    }

    long long pop_back() {
        if (tail != nullptr) {
            long long v = tail->value;
            if (tail->prev != nullptr) {
                Node* current = tail->prev;
                delete tail;
                tail = current;
                return v;
            } else {
                delete(tail);
                head = nullptr;
                tail = nullptr;
                return v;
            }
        } else {
            return 0;
        }
    }

    void add(long long v) {
        if (tail == nullptr) {
            head = new Node(v, nullptr, nullptr);
            tail = head;
        } else {
            Node* current = new Node(v, head, nullptr);
            head->prev = current;
            head = current;
        }
    }
};

int main() {
    LinkedList Bag;
    long long Amount, Capacity, x;
    std::cin >> Amount >> Capacity;
    long long i = 0;
    while ((i < Amount) && (i < Capacity)) {

        std::cin >> x;
        Bag.add(x);

        i++;
    }
    if (Amount < Capacity) {
        while (Amount > 0) {
            std::cout << Bag.pop_back() << " ";
            Amount --;
        }
    } else {
        long long back, top;
        while (i < Amount) {
            back = Bag.pop_back();
            top = Bag.pop_head();
            std::cin >> x;
            long long middle = (back + top + x) - (std::min(std::min(back, top), x)) - (std::max(std::max(back, top), x));
            Bag.add(middle);
            long long maximal = std::max(std::max(back, top), x);
            Bag.add(maximal);
            i++;
        }
        while (Capacity > 0) {
            std::cout << Bag.pop_back() << " ";
            Capacity --;
        }
    }
}