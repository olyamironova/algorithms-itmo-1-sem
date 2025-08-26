#include <iostream>
#include <vector>
#include <queue>

class BinarySearchTree {
public:
    void LevelOrderCount() {
        level_order_counting(root, balls);
    }

    void Insert(const std::string& file_name, int student_index) {
        root = Insert(root, file_name, student_index);
    }

private:
    struct Node {
        Node* left_child;
        Node* right_child;
        long long height;
        long long balance;
        std::string file_name;
        bool repeating[3] = {false, false, false};
        Node(std::string FileName) : file_name(FileName), left_child(nullptr), right_child(nullptr) {
            repeating[0] = false;
            repeating[1] = false;
            repeating[2] = false;
        }
        Node(std::string FileName, int student_index) : file_name(FileName), left_child(nullptr), right_child(nullptr) {
            repeating[student_index] = true;
        }
    };
    struct StudentBalls {
        long long amount_balls[3] = {0, 0, 0};
    };

    StudentBalls balls = {0, 0, 0};
    Node* root = nullptr;

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

    void FixHeight(Node* temp_node) {
        long long height1 = Height(temp_node->left_child);
        long long height2 = Height(temp_node->right_child);
        temp_node->height = std::max(height1, height2) + 1;
    }

    void level_order_counting(Node* temp_node, StudentBalls& balls) {
        if (temp_node == nullptr) {
            return;
        }

        std::queue<Node*> q;
        q.push(temp_node);

        while (!q.empty()) {
            Node* current_node = q.front();
            q.pop();

            for (int i = 0; i < 3; ++i) {
                if (current_node->repeating[i] && !current_node->repeating[(i + 1) % 3] && !current_node->repeating[(i + 2) % 3]) {
                    balls.amount_balls[i] += 3;
                    break;
                }
            }

            for (int i = 0; i < 3; ++i) {
                if (!current_node->repeating[i] && current_node->repeating[(i + 1) % 3] && current_node->repeating[(i + 2) % 3]) {
                    balls.amount_balls[(i + 1) % 3] += 1;
                    balls.amount_balls[(i + 2) % 3] += 1;
                    break;
                }
            }

            if (current_node->left_child != nullptr) {
                q.push(current_node->left_child);
            }

            if (current_node->right_child != nullptr) {
                q.push(current_node->right_child);
            }
        }
        std::cout << balls.amount_balls[0] << " " << balls.amount_balls[1] << " " << balls.amount_balls[2];
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

    Node* Insert(Node* future_parent, const std::string& file_name, int student_index) {
        if (future_parent == nullptr) {
            return new Node(file_name, student_index);
        }
        if (file_name == future_parent->file_name) {
            future_parent->repeating[student_index] = true;
            return future_parent;
        }
        else if (file_name < future_parent->file_name) {
            future_parent->left_child = Insert(future_parent->left_child, file_name, student_index);
        } else if (file_name > future_parent->file_name) {
            future_parent->right_child = Insert(future_parent->right_child, file_name, student_index);
        }
        return Balance(future_parent);
    }

};

int main() {
    long long n;
    std::cin >> n;
    BinarySearchTree temp_tree;
    std::string file_name;
    for (long long i = 0; i < n; ++i) {
        std::cin >> file_name;
        temp_tree.Insert(file_name, 0);
    }
    for (long long i = 0; i < n; ++i) {
        std::cin >> file_name;
        temp_tree.Insert(file_name, 1);
    }
    for (long long i = 0; i < n; ++i) {
        std::cin >> file_name;
        temp_tree.Insert(file_name, 2);
    }
    temp_tree.LevelOrderCount();
}