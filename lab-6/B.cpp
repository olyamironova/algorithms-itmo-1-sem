#include <iostream>
#include <vector>
#include <queue>

struct IntPeak {
    long long value = 0;
    long long left_child_index = 0;
    long long right_child_index = 0;
    long long balance = 0;
    IntPeak(long long Value, long long LeftChildIndex, long long RightChildIndex) {
        value = Value;
        left_child_index = LeftChildIndex;
        right_child_index = RightChildIndex;
    }
};


class BinarySearchTree {
public:
    void Building(std::vector<IntPeak>& array) {
        Building(array, root, 0);
        CalcHeight(root);
        Write(array);
    }
    void LevelOrderPrint(std::vector<IntPeak>& array, long long n) {
        LevelOrderPrint(array, root, n);
    }
    void Balance() {
        Balance(root);
    }
private:
    struct Node {
        Node* left_child;
        Node* right_child;
        long long height;
        long long balance;
        long long index = -1;
        Node(long long Index): left_child(nullptr), right_child(nullptr), height(0), balance(0), index(Index) {};
    };
    Node* root = nullptr;
    void Write(std::vector<IntPeak>& array) {
        AddBalanceToArray(array, root);
    }
    void Building(std::vector<IntPeak>& array, Node*& temp_node, long long index) {
        if (index < 0) { // к вершине от которой пришли невозможно подвесить ребенка
            return;
        }
        temp_node = new Node(index);
        if (array[index].left_child_index != -1) {
            Building(array, temp_node->left_child, array[index].left_child_index);
        }
        if (array[index].right_child_index != -1) {
            Building(array, temp_node->right_child, array[index].right_child_index);
        }
        CalcHeight(temp_node);
    }

    long long CalcHeight(Node* temp_node) { // from root
        if (temp_node == nullptr) {
            return 0;
        }
        long long left_height = CalcHeight(temp_node->left_child);
        long long right_height = CalcHeight(temp_node->right_child);
        temp_node->height = std::max(left_height, right_height) + 1;
        temp_node->balance = right_height - left_height;
        return temp_node->height;
    }

    void AddBalanceToArray(std::vector<IntPeak>& array, Node* temp_node) {
        if (temp_node == nullptr) {
            return;
        }
        array[temp_node->index].balance = temp_node->balance;
        AddBalanceToArray(array, temp_node->left_child);
        AddBalanceToArray(array, temp_node->right_child);
    }

    void LevelOrderPrint(std::vector<IntPeak>& array, Node *temp_node, long long n) {
        if (temp_node == nullptr) {
            return;
        }
        std::queue<Node*> q;
        q.push(temp_node);
        long long index_counter = 2;
        std::cout << n << "\n";
        while (!q.empty()) {
            Node* temp_node = q.front();
            q.pop();
            std::cout << array[temp_node->index].value << " ";
            if (temp_node->left_child != nullptr) {
                std::cout << index_counter++ << " ";
            } else {
                std::cout << "0" << " ";
            }
            if (temp_node->right_child != nullptr) {
                std::cout << index_counter++ << "\n";
            } else {
                std::cout << "0" << "\n";
            }
            if (temp_node->left_child != nullptr)
                q.push(temp_node->left_child);

            if (temp_node->right_child != nullptr)
                q.push(temp_node->right_child);
        }
    }
    Node* RotateRight(Node* temp_node) {
        Node* new_peak = temp_node->left_child;
        temp_node->left_child = new_peak->right_child;
        new_peak->right_child = temp_node;
        CalcHeight(temp_node);
        CalcHeight(new_peak);
        return new_peak;
    }

    Node* RotateLeft(Node* temp_node) {
        Node* new_peak = temp_node->right_child;
        temp_node->right_child = new_peak->left_child;
        new_peak->left_child = temp_node;
        CalcHeight(temp_node);
        CalcHeight(new_peak);
        return new_peak;
    }
    Node* Balance(Node* root) {
        CalcHeight(root);
        if (root->balance == 2) {
            if (((root->right_child)->balance) < 0) {
                root->right_child = RotateRight(root->right_child);
            }
            root = RotateLeft(root);
        }
        if (root->balance == -2) {
            if (((root->left_child)->balance) > 0) {
                root->left_child = RotateLeft(root->left_child);
            }
            root = RotateRight(root);
        }
        this->root = root;
        return root;
    }

};

int main() {
    long long n;
    std::cin >> n;
    long long key, left, right;
    std::vector<IntPeak> array;
    for (long long i = 0; i < n; ++i) {
        std::cin >> key >> left >> right;
        IntPeak peak(key, left - 1, right - 1);
        array.push_back(peak);
    }
    BinarySearchTree temp_tree;
    temp_tree.Building(array);
    temp_tree.Balance();
    temp_tree.LevelOrderPrint(array, n);
}