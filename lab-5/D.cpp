#include <iostream>
#include <vector>
#include <queue>

class BinarySearchTree {
public:
    void Insert(long long value) {
        root = Insert(root, value);
    }

    void PrintRightNodes() {
        PrintRightNodes(root);
    }
private:
    struct Node {
        long long value;
        Node* left_child;
        Node* right_child;
        Node(long long Value) : value(Value), left_child(nullptr), right_child(nullptr) {};
    };

    Node* root = nullptr;

    Node* Insert(Node* future_parent, long long value) {
        if (future_parent == nullptr) {
            return new Node(value);
        } else if (value < future_parent->value) {
            future_parent->left_child = Insert(future_parent->left_child, value);
        } else if (value > future_parent->value) {
            future_parent->right_child = Insert(future_parent->right_child, value);
        }
        return future_parent;
    }

    void PrintRightNodes(Node* temp_node) {
        if (temp_node == nullptr) {
            return;
        }
        std::queue<Node*> q;
        q.push(temp_node);

        while (!q.empty()) {
            long long size = q.size();

            for (long long i = 0; i < size; ++i) {
                Node* current = q.front();
                q.pop();
                // eсли текущий элемент - последний на уровне, выводим его значение
                if (i == size - 1) {
                    std::cout << current->value << " ";
                }
                // добавляем детей в очередь для следующего уровня
                if (current->left_child) {
                    q.push(current->left_child);
                }
                if (current->right_child) {
                    q.push(current->right_child);
                }
            }
        }
    }
};

int main() {
    long long n;
    std::cin >> n;
    long long value;
    BinarySearchTree temp_tree;
    for (long long i = 0; i < n; ++i) {
        std::cin >> value;
        temp_tree.Insert(value);
    }
    temp_tree.PrintRightNodes();
}