#include <iostream>
#include <vector>
#include <stack>

class BinarySearchTree {
public:
    bool CheckPostOrder(const std::vector<long long>& array) const {
        return check_post_order(array);
    }

    void BuildPostOrder() {
        build_post_order();
    }

    void BuildTreeFromPreorder(const std::vector<long long>& preorder) {
        root = buildTreeFromPreorder(preorder);
    }

private:
    struct Node {
        long long value;
        Node* left_child;
        Node* right_child;

        Node(long long Value) : value(Value), left_child(nullptr), right_child(nullptr) {};
    };

    Node* root = nullptr;
    std::vector<long long> post_order;

    Node* buildTreeFromPreorder(const std::vector<long long>& preorder) {
        long long n = preorder.size();
        if (n == 0) return nullptr;

        Node* root = new Node(preorder[0]);

        std::stack<Node*> s;
        s.push(root);

        // preorder
        for (long long i = 1; i < n; ++i) {
            Node* node = nullptr;
            // ищем вершину, к которой нужно подвесить текущего потомка
            while (!s.empty() && s.top()->value <= preorder[i]) {
                node = s.top();
                s.pop();
            }
            // подвешиваем потомка к вершине
            Node* child = new Node(preorder[i]);
            if (node) {
                node->right_child = child;
            } else {
                s.top()->left_child = child;
            }
            // добавляем текущего потомка в стек
            s.push(child);
        }

        return root;
    }

    void build_post_order() {
        build_post_order_helper(root);
    }

    void build_post_order_helper(Node* temp_node) {
        if (temp_node != nullptr) {
            build_post_order_helper(temp_node->left_child);
            build_post_order_helper(temp_node->right_child);
            post_order.push_back(temp_node->value);
        }
    }

    bool check_post_order(const std::vector<long long>& values) const {
        return values == post_order;
    }
};

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);

    long long n;
    std::cin >> n;

    BinarySearchTree temp_tree;
    std::vector<long long> preorder(n);
    std::vector<long long> inorder(n);
    std::vector<long long> postorder(n);

    for (long long i = 0; i < n; ++i) {
        std::cin >> preorder[i];
    }

    for (long long i = 0; i < n; ++i) {
        std::cin >> inorder[i];
    }

    for (long long i = 0; i < n; ++i) {
        std::cin >> postorder[i];
    }

    temp_tree.BuildTreeFromPreorder(preorder);
    for (long long i = 0; i < n - 1; ++i) {
        if (inorder[i] > inorder[i + 1]) {
            std::cout << "NO";
            return 0;
        }
    }

    temp_tree.BuildPostOrder();
    if (!temp_tree.CheckPostOrder(postorder)) {
        std::cout << "NO";
        return 0;
    }

    std::cout << "YES";
    return 0;
}