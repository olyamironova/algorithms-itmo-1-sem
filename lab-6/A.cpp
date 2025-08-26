#include <iostream>
#include <vector>

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
    for (long long i = 0; i < n; ++i) {
        std::cout << array[i].balance << "\n";
    }
}