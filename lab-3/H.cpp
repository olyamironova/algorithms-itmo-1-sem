#include <iostream>

struct Node {
    std::pair <long long, long long> coordinates;
    Node* next = nullptr;
    Node* prev = nullptr;
    Node(std::pair <long long, long long> coordinatess, Node* Next, Node* Prev) {
        coordinates = coordinatess;
        next = Next;
        prev = Prev;
    }
};

struct LinkedList {
    Node* head = nullptr;
    Node* tail = nullptr;
    std::pair <long long, long long> pop_back() {
        std::pair <long long, long long> coordinatess = tail->coordinates;
        Node* current = tail->prev;
        delete(tail);
        tail = current;
        return coordinatess;
    }

    std::pair <long long, long long> pop_head() {
        std::pair <long long, long long> coordinatess = head->coordinates;
        Node* current = head->next;
        delete(head);
        head = current;
        return coordinatess;
    }

    void add(std::pair <long long, long long> coordinates) {
        if (tail == nullptr) {
            head = new Node(coordinates, nullptr, nullptr);
            tail = head;
        } else {
            Node* current = new Node(coordinates, head, nullptr);
            head->prev = current;
            head = current;
        }
    }

    long long top_h() {
        return head->coordinates.second;
    }

    long long top_abscissa() {
        return head->coordinates.first;
    }
};

int main() {
    long long n;
    std::cin >> n;
    LinkedList Board;
    Board.add(std::make_pair(0, - 1));
    long long Result = 0, x = 0, h = 0, area = 0, result = 0, hPrev;
    for (int i = 1; i <= n + 1; i++) {
        if (i <= n) {
            std::cin >> h;
        } else {
            h = 0;
        }
        x = i;
        while (h <= Board.top_h()) {
            x = Board.top_abscissa();
            hPrev = Board.top_h();
            Board.pop_head();
            area = hPrev * (i - x);
            if (area > Result) {
                Result = area;
            }
        }

        Board.add(std::make_pair(x, h));
    }
    std::cout << Result;
}
