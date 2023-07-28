#include "MerkleTree.h"

// Find the value of height that provides enough slots for storing data.
int MerkleTree::getHeight(int numberOfData) {
    int leaves = 1;
    while (leaves < numberOfData) {
        height++;
        leaves = leaves * 2;
    }
    return height;
}

// Calculate the hash string of data.
std::string MerkleTree::calculate_hash(const std::string& data) {
    std::hash<std::string> str_hash;
    return std::to_string(str_hash(data));
}

// Build Merkle Tree based on hash value list.
void MerkleTree::buildMerkleTreeHelper(
    Node* node, int curHeight, std::vector<std::string> listOfData
) {
    if (curHeight >= height) {
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

    curHeight++;
    node->left = new Node();
    node->right = new Node();
    buildMerkleTreeHelper(node->right, curHeight, listOfData);
    buildMerkleTreeHelper(node->left, curHeight, listOfData);
    node->key = calculate_hash(node->left->key + node->right->key);
}

void MerkleTree::buildMerkleTree(const std::vector<std::string>& listOfData) {
    buildMerkleTreeHelper(root, 0, listOfData);
}

bool MerkleTree::searchInMerkleTreeHelper(Node* node, const std::string& targetData) {
    if (!node) {
        return false;
    }

    if (node->key == targetData) {
        return true;
    }

    return searchInMerkleTreeHelper(node->left, targetData) ||
           searchInMerkleTreeHelper(node->right, targetData);
}

bool MerkleTree::searchInMerkleTree(const std::string& targetData) {
    return searchInMerkleTreeHelper(root, targetData);
}

void MerkleTree::deleteMerkleTreeHelper(Node* node) {
    if (node == nullptr) return;
    deleteMerkleTreeHelper(node->left);
    deleteMerkleTreeHelper(node->right);
    delete node;
}
