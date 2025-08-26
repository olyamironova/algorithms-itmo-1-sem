#include <iostream>
#include <queue>

class BinarySearchTree {
private:
    struct Node {
        Node *left_child;
        Node *right_child;
        long long value;

        Node(long long Value) : left_child(nullptr), right_child(nullptr), value(Value) {}
    };

    Node *root = nullptr;

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

    bool Empty() {
        return root == nullptr;
    }

    void inOrderPrintWithoutLastSpace() {
        bool isFirst = true;
        inOrderPrintHelper(root, isFirst);
        std::cout << std::endl;
    }

    Node *merge_and_clear(BinarySearchTree &second_tree) {
        root = mergeAndClearRecursive(root, second_tree.root);
        second_tree.root = nullptr;
        return root;
    }

    void LevelOrderPrint() {
        levelOrderPrint(root);
    }

private:
    Node *mergeAndClearRecursive(Node *node1, Node *node2) {
        if (!node2) {
            return node1;
        }
        if (!node1) {
            return node2;
        }

        node2->left_child = mergeAndClearRecursive(node1, node2->left_child);
        node2->right_child = mergeAndClearRecursive(node1, node2->right_child);

        if (node2) {
            node1 = insert(node1, node2->value);
        }

        delete node2;

        return node1;
    }


    void inOrderPrintHelper(Node *node, bool &isFirst) {
        if (node) {
            inOrderPrintHelper(node->left_child, isFirst);

            if (!isFirst) {
                std::cout << " ";
            }

            std::cout << node->value;
            isFirst = false;

            inOrderPrintHelper(node->right_child, isFirst);
        }
    }

    Node *minimum(Node *temp_node) {
        if (temp_node->left_child == nullptr) {
            return temp_node;
        }
        return minimum(temp_node->left_child);
    }

    bool exists(Node *temp_node, long long value) {
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


    Node *insert(Node *future_parent, long long value) {
        if (future_parent == nullptr) {
            return new Node(value);
        } else if (value < future_parent->value) {
            future_parent->left_child = insert(future_parent->left_child, value);
        } else if (value > future_parent->value) {
            future_parent->right_child = insert(future_parent->right_child, value);
        }
        return future_parent;
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
        return temp_node;
    }

    void levelOrderPrint(Node *temp_node) {
        if (temp_node == nullptr) {
            return;
        }
        std::queue<Node *> q;
        q.push(temp_node);

        while (!(q.empty())) {
            Node *temp_node = q.front();
            q.pop();
            std::cout << temp_node->value << " ";

            if (temp_node->left_child != nullptr)
                q.push(temp_node->left_child);

            if (temp_node->right_child != nullptr)
                q.push(temp_node->right_child);
        }
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    long long n;
    std::cin >> n;
    std::string command;
    long long account;
    long long id;
    BinarySearchTree first_tree;
    BinarySearchTree second_tree;
    for (long long i = 0; i < n; ++i) {
        std::cin >> command;
        if (command == "buy") {
            std::cin >> account >> id;
            if (account == 1) {
                first_tree.Insert(id);
            } else if (account == 2) {
                second_tree.Insert(id);
            }
        } else if (command == "sell") {
            std::cin >> account >> id;
            if (account == 1) {
                first_tree.Delete(id);
            } else if (account == 2) {
                second_tree.Delete(id);
            }
        } else if (command == "merge") {
            first_tree.merge_and_clear(second_tree);
            if (!first_tree.Empty()) {
                first_tree.inOrderPrintWithoutLastSpace();
            }
        }
    }
};