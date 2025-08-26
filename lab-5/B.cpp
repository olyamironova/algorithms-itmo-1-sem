#include <iostream>

class BinarySearchTree {
public:
    void Insert(long long value) {
        if (!exists(root, value)) {
            root = insert(root, value);
        } else {
            return;
        }
    }

    void Delete(long long value) {
        if (exists(root, value)) {
            root = delete_(root, value);
        } else {
            return;
        }
    }

    void exists(long long value) {
         if (exists(root, value)) {
             std::cout << "true" << "\n";
         } else {
             std::cout << "false" << "\n";
         }
    }

    void next_(long long value) {
        Node* x = next(value);
        if (x != nullptr) {
            std::cout << x->value << "\n";
        } else {
            std::cout << "none" << "\n";
        }
    }

    void prev_(long long value) {
        Node* x = prev(value);
        if (x != nullptr) {
            std::cout << x->value << "\n";
        } else {
            std::cout << "none" << "\n";
        }
    }
    
private:
    struct Node {
        Node* left_child;
        Node* right_child;
        long long value;
        Node(long long Value) : left_child(nullptr), right_child(nullptr), value(Value) {}
    };

    Node* root = nullptr;
    
    Node* minimum(Node* temp_node) {
        if (temp_node->left_child == nullptr) {
            return temp_node;
        }
        return minimum(temp_node->left_child);
    }

    Node* next(long long value) {
        Node* current = root;
        Node* successor = nullptr;
        while (current != nullptr) {
            if (current->value > value) {
                successor = current;
                current = current->left_child;
            } else {
                current = current->right_child;
            }
        }
        return successor;
    }

    Node* prev(long long value) {
        Node* current = root;
        Node* successor = nullptr;
        while (current != nullptr) {
            if (current->value < value) {
                successor = current;
                current = current->right_child;
            } else {
                current = current->left_child;
            }
        }
        return successor;
    }
    bool exists(Node* temp_node, long long value) {
        if (temp_node == nullptr) {
            return false;
        }
        if (value < temp_node->value) {
            return exists(temp_node->left_child, value);
        } else if (value > temp_node->value) {
            return exists(temp_node->right_child, value);
        }
        return true;
    }


    Node* insert(Node* future_parent, long long value) {
        if (future_parent == nullptr) {
            return new Node(value);
        } else if (value < future_parent->value) {
            future_parent->left_child = insert(future_parent->left_child, value);
        } else if (value > future_parent->value) {
            future_parent->right_child = insert(future_parent->right_child, value);
        }
        return future_parent;
    }

    Node* delete_(Node* temp_node, long long value) {
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
        return temp_node;
    }

};

int main() {
    BinarySearchTree temp_tree;
    std::string command;
    std::string value_;
    long long value;
    while (std::cin >> command) {
        std::cin >> value;
        if (command == "insert") {
            temp_tree.Insert(value);
        }
        if (command == "delete") {
            temp_tree.Delete(value);
        }
        if (command == "exists") {
            temp_tree.exists(value);
        }
        if (command == "next") {
            temp_tree.next_(value);
        }
        if (command == "prev") {
            temp_tree.prev_(value);
        }
    }
}