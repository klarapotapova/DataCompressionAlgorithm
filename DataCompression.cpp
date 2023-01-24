#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

class HuffmanTree {
public:
    struct Node {
        char c;
        int freq;
        Node* left;
        Node* right;

        Node(char c, int freq) : c(c), freq(freq), left(nullptr), right(nullptr) {}

        bool operator<(const Node& other) const {
            return freq > other.freq;
        }
    };

    HuffmanTree(const std::string& s) {
        std::unordered_map<char, int> freq;
        for (const auto& c : s) {
            freq[c]++;
        }

        std::priority_queue<Node> q;
        for (const auto& [c, f] : freq) {
            q.push(Node(c, f));
        }

        while (q.size() > 1) {
            Node* left = new Node(q.top()); q.pop();
            Node* right = new Node(q.top()); q.pop();

            Node* parent = new Node(0, left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            q.push(*parent);
        }

        root = new Node(q.top());
    }

    std::unordered_map<char, std::string> getCodes() {
        std::unordered_map<char, std::string> codes;
        encode(root, "", codes);
        return codes;
    }

private:
    Node* root;

    void encode(Node* node, std::string code, std::unordered_map<char, std::string>& codes) {
        if (!node) {
            return;
        }
        if (node->c) {
            codes[node->c] = code;
        } else {
            encode(node->left, code + "0", codes);
            encode(node->right, code + "1", codes);
        }
    }
};

std::string compress(const std::string& s) {
    HuffmanTree tree(s);
    auto codes = tree.getCodes();

    std::string compressed;
    for (const auto& c : s) {
        compressed += codes[c];
    }
    return compressed;
}

int main() {
    std::string original;
    std::cout << "Enter a string to compress: ";
    std::getline(std::cin, original);

    std::string compressed = compress(original);
    std::cout << "Compressed string: " << compressed << std::endl;

    return 0;
}
