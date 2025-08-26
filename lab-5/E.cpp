#include <iostream>
#include <queue>

class BinarySearchTree {
public:
    void LevelOrderCounting() {
        level_order_counting(root, balls);
        std::cout << balls.balls_[0] << " " << balls.balls_[1] << " " << balls.balls_[2];
    }

    void Processing(std::string FileName, int index_student) {
        processing_file_name(FileName, index_student);
    }

private:
    struct Node {
        std::string file_name_;
        Node* left_child;
        Node* right_child;
        bool repeating[3];
        Node(std::string FileName) : file_name_(FileName), left_child(nullptr), right_child(nullptr) {
            repeating[0] = false;
            repeating[1] = false;
            repeating[2] = false;
        }
    };

    struct student_balls {
        long long balls_[3] = {0, 0, 0};
    };

    student_balls balls = {0, 0, 0};
    Node* root = nullptr;

    Node* insert_(Node* future_parent, std::string file_name_) {
        if (future_parent == nullptr) {
            return new Node(file_name_);
        }
        if (file_name_ < future_parent->file_name_) {
            future_parent->left_child = insert_(future_parent->left_child, file_name_);
        } else if (file_name_ > future_parent->file_name_) {
            future_parent->right_child = insert_(future_parent->right_child, file_name_);
        }
        return future_parent;
    }

    Node* search_(Node* temp_node, std::string file_name_) {
        if (temp_node == nullptr || file_name_ == temp_node->file_name_) {
            return temp_node;
        }
        if (file_name_ < temp_node->file_name_) {
            return search_(temp_node->left_child, file_name_);
        } else {
            return search_(temp_node->right_child, file_name_);
        }
    }

    void processing_file_name(std::string file_name_, int index_student_) {
        if (root == nullptr) {
            root = insert_(root, file_name_);
            root->repeating[index_student_] = true;
        } else {
            Node* new_node = search_(root, file_name_);
            if (new_node == nullptr) {
                root = insert_(root, file_name_);
                new_node = search_(root, file_name_);
            }
            new_node->repeating[index_student_] = true;
        }
    }

    void level_order_counting(Node* temp_node, student_balls& balls) {
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
                    balls.balls_[i] += 3;
                    break;
                }
            }

            for (int i = 0; i < 3; ++i) {
                if (!current_node->repeating[i] && current_node->repeating[(i + 1) % 3] && current_node->repeating[(i + 2) % 3]) {
                    balls.balls_[(i + 1) % 3] += 1;
                    balls.balls_[(i + 2) % 3] += 1;
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
    }
};

int main() {
    long long n;
    std::cin >> n;

    BinarySearchTree temp_tree;
    std::string FileName;

    for (long long i = 0; i < n; ++i) {
        std::cin >> FileName;
        temp_tree.Processing(FileName, 0);
    }

    for (long long i = 0; i < n; ++i) {
        std::cin >> FileName;
        temp_tree.Processing(FileName, 1);
    }

    for (long long i = 0; i < n; ++i) {
        std::cin >> FileName;
        temp_tree.Processing(FileName, 2);
    }

    temp_tree.LevelOrderCounting();

    return 0;
}