#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>

struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int f, Node* l = nullptr, Node* r = nullptr) : data(ch), freq(f), left(l), right(r) {}
};

struct CompareNodes {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->freq > rhs->freq;
    }
};

void generateHuffmanCode(Node* node, const std::string& code, std::unordered_map<char, std::string>& huffmanCode) {
    if (node) {
        if (node->left) {
            generateHuffmanCode(node->left, code + "0", huffmanCode);
        }
        if (node->right) {
            generateHuffmanCode(node->right, code + "1", huffmanCode);
        }
        if (!node->left && !node->right) {
            huffmanCode[node->data] = code;
        }
    }
}

void buildHuffmanTree(std::string s, std::unordered_map<char, std::string>& huffmanCode) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> minHeap;

    std::unordered_map<char, int> freqMap;
    for (char ch : s) {
        freqMap[ch]++;
    }

    for (const auto& pair : freqMap) {
        minHeap.push(new Node(pair.first, pair.second));
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();
        Node* merged = new Node('$', left->freq + right->freq, left, right);
        minHeap.push(merged);
    }

    Node* root = minHeap.top();
    std::string code;
    generateHuffmanCode(root, code, huffmanCode);
}

void encode(std::string s, const std::unordered_map<char, std::string>& huffmanCode) {
    int encodedLength = 0;
    for (char ch : s) {
        encodedLength += huffmanCode.at(ch).size();
    }

    std::cout << encodedLength << "\n";
}

int main() {
    std::string s;
    std::cin >> s;

    std::unordered_map<char, std::string> huffmanCode;
    buildHuffmanTree(s, huffmanCode);

    encode(s, huffmanCode);

    return 0;
}
