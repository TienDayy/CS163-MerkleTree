#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    string key;
    Node* left;
    Node* right;
};

vector<string> listOfData = {"data1", "data2", "data3", "data4", "data5"};
Node* root = nullptr;
int height;

// Tìm chiều cao height sao cho đủ leaves để chứa data
int getHeight(int numberOfData) {
    int leaves = 1, h = 0;
    while (leaves < numberOfData) {
        h++;
        leaves = leaves * 2;
    }
    return h;
}

// Tính toán giá trị băm của một dữ liệu
string calculate_hash(const string& data) {
    hash<string> str_hash;
    return to_string(str_hash(data));
}

// Xây dựng cây Merkle từ danh sách các giá trị băm
void build_merkle_tree(int current_height, Node* node) {
    if (current_height >= height) {
        if (listOfData.size() == 0) {
            node->key = "";
        } else {
            node->key = listOfData[listOfData.size() - 1];
            listOfData.pop_back();
        }
        node->left = nullptr;
        node->right = nullptr;
        return;
    }
    current_height++;
    node->left = new Node;
    node->right = new Node;
    build_merkle_tree(current_height, node->right);
    build_merkle_tree(current_height, node->left);
    node->key = calculate_hash(node->left->key + node->right->key);
}

void delete_merkle_tree(Node* root) {
    if (root == nullptr) return;
    delete_merkle_tree(root->left);
    delete_merkle_tree(root->right);
    delete root;
}
int main() {
    // Build
    height = getHeight(listOfData.size());
    if (listOfData.size() > 0) {
        root = new Node;
        build_merkle_tree(0, root);
    } else
        cout << "No data to build";

    // Cout root(hash)
    cout << root->key << '\n';

    // Delete
    delete_merkle_tree(root);

    return 0;
}
