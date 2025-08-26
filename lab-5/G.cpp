#include <iostream>

struct Node {
    Node* left_child;
    Node* right_child;
    Node* parent;
    long long sumBST;
    long long max_;
    long long min_;
    long long value;
    bool isBST = true;
    Node(long long Value) : value(Value), left_child(nullptr), right_child(nullptr), parent(nullptr), isBST(true), sumBST(Value), max_(Value), min_(Value) {};
    Node(long long Value, Node* Left_child, Node* Right_child, Node* Parent) : value(Value), left_child(Left_child), right_child(Right_child), parent(Parent), isBST(true), sumBST(Value), max_(Value), min_(Value) {};
};

void counting_summ(Node* root) {
    if (root != nullptr) {
        counting_summ(root->left_child);
        counting_summ(root->right_child);
        if (root->parent != nullptr) {
            root->parent->sumBST += root->sumBST;
        }
    }
}

void pre_order_max_summ(Node *temp_node, long long& max_summ) {
    if (temp_node != nullptr) {
        if ((max_summ < temp_node->sumBST) && (temp_node->isBST)) {
            max_summ = temp_node->sumBST;
        }
        pre_order_max_summ(temp_node->left_child, max_summ);
        pre_order_max_summ(temp_node->right_child, max_summ);
    }
}

void is_bst(Node* root) {
    if (root != nullptr) {
        is_bst(root->left_child);
        is_bst(root->right_child);
        if (root->left_child != nullptr) {
            if ((root->left_child->max_ >= root->min_) or (!(root->left_child->isBST))) {
                root->isBST = false;
            } else {
                root->min_ = root->left_child->min_;
            }
        }
        if (root->right_child != nullptr) {
            if ((root->right_child->min_ <= root->max_) or (!root->right_child->isBST)) {
                root->isBST = false;
            } else {
                root->max_ = root->right_child->max_;
            }
        }
    }
}

int main() {
    long long value;
    std::cin >> value;
    Node* root = new Node(value);
    Node* temp_node = root;
    std::string command;
    while (std::cin >> command) {
        if (command == "l") {
            std::cin >> value;
            Node* new_node = new Node(value, nullptr, nullptr, temp_node);
            temp_node->left_child = new_node;
            temp_node = new_node;
        } else if (command == "r") {
            std::cin >> value;
            Node* new_node = new Node(value, nullptr, nullptr, temp_node);
            temp_node->right_child = new_node;
            temp_node = new_node;
        } else if (command == "u") {
            temp_node = temp_node->parent;
            if (temp_node == nullptr) {
                break;
            }
        }
    }
    long long max = 0;
    counting_summ(root);
    is_bst(root);
    pre_order_max_summ(root, max);
    std::cout << max;
}