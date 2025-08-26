#include <iostream>

class StringBinarySearchTree {
public:
    void Insert(const std::string& message_name) {
        root = Insert(root, message_name);
    }

    long long GetFreeStorage() {
        return global_memory;
    }
private:
    struct Node {
        Node* left_child;
        Node* right_child;
        long long height;
        long long balance;
        std::string message_name;
        long long free_storage;
        Node (std::string MessageName, long long FreeStorage) : left_child(nullptr), right_child(nullptr), height(1), balance(0), message_name(MessageName), free_storage(FreeStorage) {};
    };

    Node* root = nullptr;
    long long global_memory = 0;

    long long Height(Node* temp_node) {
        if (temp_node) {
            return temp_node->height;
        } else {
            return 0;
        }
    }

    long long BalanceFactor(Node* temp_node) {
        return Height(temp_node->right_child) - Height(temp_node->left_child);
    }
    long long maybe_insert(const std::string& message_name) {
        long long unique_element = 0;
        bool repeating[128] = {false};
        for (int i = 0; i < message_name.size(); ++i) {
            if (repeating[int(message_name[i])] == false) {
                ++unique_element;
                repeating[int(message_name[i])] = true;
            } else {
                continue;
            }
        }
        return unique_element;
    }

    void FixHeight(Node* temp_node) {
        long long height1 = Height(temp_node->left_child);
        long long height2 = Height(temp_node->right_child);
        temp_node->height = std::max(height1, height2) + 1;
    }

    Node* RotateRight(Node* temp_node) {
        Node* new_peak = temp_node->left_child;
        temp_node->left_child = new_peak->right_child;
        new_peak->right_child = temp_node;
        FixHeight(temp_node);
        FixHeight(new_peak);
        return new_peak;
    }

    Node* RotateLeft(Node* temp_node) {
        Node* new_peak = temp_node->right_child;
        temp_node->right_child = new_peak->left_child;
        new_peak->left_child = temp_node;
        FixHeight(temp_node);
        FixHeight(new_peak);
        return new_peak;
    }

    Node* Balance(Node* temp_node) {
        FixHeight(temp_node);
        if (BalanceFactor(temp_node) == 2) {
            if (BalanceFactor(temp_node->right_child) < 0) {
                temp_node->right_child = RotateRight(temp_node->right_child);
            }
            temp_node = RotateLeft(temp_node);
        }
        if (BalanceFactor(temp_node) == -2) {
            if (BalanceFactor(temp_node->left_child) > 0) {
                temp_node->left_child = RotateLeft(temp_node->left_child);
            }
            temp_node = RotateRight(temp_node);
        }
        return temp_node;
    }

    Node* Insert(Node* future_parent, const std::string& message_name) {
        if (future_parent == nullptr) {
            long long free_storage = maybe_insert(message_name);
            return new Node(message_name, free_storage);
        }
        if (message_name == future_parent->message_name) {
            global_memory += future_parent->free_storage;
            return Balance(future_parent);
        }
        else if (message_name < future_parent->message_name) {
            future_parent->left_child = Insert(future_parent->left_child, message_name);
        } else if (message_name > future_parent->message_name) {
            future_parent->right_child = Insert(future_parent->right_child, message_name);
        }
        return Balance(future_parent);
    }

};

int main() {
    long long n;
    std::cin >> n;
    StringBinarySearchTree temp_tree;
    std::string message_name;
    for (long long i = 0; i < n; ++i) {
        std::cin >> message_name;
        temp_tree.Insert(message_name);
    }
    std::cout << temp_tree.GetFreeStorage();
}