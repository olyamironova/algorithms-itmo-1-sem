#include <iostream>

class BinarySearchTree {
public:
    void Insert(long long value) {
        root = Insert(root, value);
        FixHeight(root);
    }

    void Delete(long long value) {
        root = delete_key(root, value);
    }

    bool Exist(long long value) {
        return Exist(root, value);
    }

    long long GetRootBalance() {
        if (root) {
            return root->balance;
        } else {
            return 0;
        }
    }

    bool Empty() {
        return is_empty();
    }
    
    struct Node {
        Node* left_child;
        Node* right_child;
        long long value;
        long long height;
        long long balance;
        Node(long long Value) : left_child(nullptr), right_child(nullptr), height(1), balance(0), value(Value) {}
    };
    Node* root = nullptr;
    
private:

    bool is_empty() {
        return (!root);
    }

    bool Exist(Node* temp_node, long long value) {
        if (temp_node == nullptr) {
            return false;
        }
        if (value < temp_node->value) {
            return Exist(temp_node->left_child, value);
        } else if (value > temp_node->value) {
            return Exist(temp_node->right_child, value);
        }
        return true;
    }

    long long Height(Node* temp_node) {
        if (temp_node) {
            return temp_node->height;
        } else {
            return 0;
        }
    }

    long long BalanceFactor(Node* temp_node) {
        if (temp_node) {
            return Height(temp_node->right_child) - Height(temp_node->left_child);
        } else {
            return 0;
        }
    }

    void FixHeight(Node* temp_node) {
        long long height1 = Height(temp_node->left_child);
        long long height2 = Height(temp_node->right_child);
        temp_node->height = std::max(height1, height2) + 1;
        temp_node->balance = BalanceFactor(temp_node);
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
        if (temp_node != nullptr) {
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
        }
        return temp_node;
    }

    Node* Insert(Node* future_parent, long long value) {
        if (future_parent == nullptr) {
            return new Node(value);
        }
        if (value < future_parent->value) {
            future_parent->left_child = Insert(future_parent->left_child, value);
        } else if (value > future_parent->value) {
            future_parent->right_child = Insert(future_parent->right_child, value);
        } else {

        }
        return Balance(future_parent);
    }

    Node* find_max(Node* p) {
        Node* temp_node = p;
        while (temp_node && temp_node->right_child) {
            temp_node = temp_node->right_child;
        }
        return temp_node;
    }

    Node* delete_key(Node* root, int z) {
        if (root == nullptr) {
            return root;
        }
        if (z < root->value) {
            root->left_child = delete_key(root->left_child, z);
        } else if (z > root->value) {
            root->right_child = delete_key(root->right_child, z);
        } else {
            if (root->left_child == nullptr) {
                Node* temp = root->right_child;
                delete root;
                return Balance(temp);
            } else if (root->right_child == nullptr) {
                Node* temp = root->left_child;
                delete root;
                return Balance(temp);
            }

            Node* temp = find_max(root->left_child);
            root->value = temp->value;
            root->left_child = delete_key(root->left_child, temp->value);
        }

        return Balance(root);
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    BinarySearchTree temp_tree;
    long long n;
    std::cin >> n;
    std::string command;
    long long value;
    for (long long i = 0; i < n; ++i) {
        std::cin >> command >> value;
        if (command == "A") {
            temp_tree.Insert(value);
            std::cout << temp_tree.GetRootBalance() << '\n';
        } else if (command == "D") {
            if(temp_tree.Exist(value))
                temp_tree.Delete(value);
            std::cout << temp_tree.GetRootBalance() << '\n';
        } else if (command == "C") {
            if (temp_tree.Empty()) {
                std::cout << "N" << '\n';
            }
            else {
                if (temp_tree.Exist(value)) {
                    std::cout << "Y" << '\n';
                } else {
                    std::cout << "N" << '\n';
                }
            }
        }
    }
}