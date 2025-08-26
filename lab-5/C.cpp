#include <iostream>

class BinarySearchTree {
public:
    void Insert(long long value) {
        root = insert(root, value);
    }

    void Delete(long long value) {
        root = delete_(root, value);
    }
     long long kthLargest(long long k) {
        Node* x = jump_traverse(root, k, 0);
        if (x != nullptr) {
            return x->value;
        } else {
            return 0;
        }
    }

    struct Node {
        Node *left_child;
        Node *right_child;
        long long value;
        long long amount_element;

        Node(long long Value) : left_child(nullptr), right_child(nullptr), value(Value), amount_element(1) {}
    };

    Node *root = nullptr;

    void AmountFactor(Node* temp_node) {
        long long left_amount;
        long long right_amount;
        if (temp_node->left_child != nullptr) {
            left_amount = temp_node->left_child->amount_element;
        } else {
            left_amount = 0;
        }
        if (temp_node->right_child != nullptr) {
            right_amount = temp_node->right_child->amount_element;
        } else {
            right_amount = 0;
        }
        temp_node->amount_element = left_amount + right_amount + 1;
    }
    Node *insert(Node *future_parent, long long value) {
        if (future_parent == nullptr) {
            return new Node(value);
        } else if (value < future_parent->value) {
            future_parent->left_child = insert(future_parent->left_child, value);
        } else if (value > future_parent->value) {
            future_parent->right_child = insert(future_parent->right_child, value);
        }
        AmountFactor(future_parent);
        return future_parent;
    }

    Node *minimum(Node *temp_node) {
        if (temp_node->left_child == nullptr) {
            return temp_node;
        }
        return minimum(temp_node->left_child);
    }

    Node *delete_(Node *temp_node, long long value) {
        if (temp_node == nullptr) {
            return temp_node;
        }
        if (value < temp_node->value) {
            temp_node->left_child = delete_(temp_node->left_child, value);
        } else if (value > temp_node->value) {
            temp_node->right_child = delete_(temp_node->right_child, value);
        } else if ((temp_node->left_child != nullptr) && (temp_node->right_child != nullptr)) {
            temp_node->value = minimum(temp_node->right_child)->value;
            temp_node->right_child = delete_(temp_node->right_child, temp_node->value);
        } else {
            if (temp_node->left_child != nullptr) {
                temp_node = temp_node->left_child;
            } else if (temp_node->right_child != nullptr) {
                temp_node = temp_node->right_child;
            } else {
                temp_node = nullptr;
            }
        }
        if (temp_node != nullptr) {
            AmountFactor(temp_node);
        }
        return temp_node;
    }

    Node* jump_traverse(Node* temp_node, const long long& k, long long visited) {
        long long r;
        if (temp_node->right_child == nullptr) {
            r = 0;
        } else {
            r = (temp_node->right_child)->amount_element;
        }
        if ((visited + r >= k) && (temp_node->right_child != nullptr)) {
            return jump_traverse(temp_node->right_child, k, visited);
        } else if (visited + r == k - 1) {
            return temp_node;
        } else if ((visited + r < k - 1) && (temp_node->left_child != nullptr)) {
            return jump_traverse(temp_node->left_child, k, visited + r + 1);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    BinarySearchTree temp_tree;
    long long command;
    long long value;
    long long n;
    std::cin >> n;
    for (long long i = 0; i < n; ++i) {
        std::cin >> command >> value;
        if (command == 1) {
            temp_tree.Insert(value);
        }
        if (command == 0) {
            std::cout << temp_tree.kthLargest(value) << "\n";
        }
        if (command == -1) {
            temp_tree.Delete(value);
        }
    }
}