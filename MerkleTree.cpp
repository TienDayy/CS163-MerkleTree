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

// As mentioned earlier, Merkle trees are immutable, so we can't directly update data in
// a Merkle tree. However, if we need to modify data, we can create a new Merkle tree
// that reflects the changes, then compare the old root hash with the new root hash to
// determine the differences. Any nodes whose hashes are different between the old and new
// trees will represent the changes made.

void MerkleTree::updateMerkleTreeHelper(
    Node* node, const std::string& targetData, const std::string& newData
) {
    if (!node) {
        return;
    }

    if (node->key == targetData) {
        node->key = newData;
        return;
    }

    updateMerkleTreeHelper(node->left, targetData, newData);
    updateMerkleTreeHelper(node->right, targetData, newData);
}

void MerkleTree::updateMerkleTree(
    const std::string& targetData, const std::string& newData
) {
    updateMerkleTreeHelper(root, targetData, newData);
}

// Similarly to updating data, direct deletion of data is not possible in a Merkle tree
// due to its immutable nature. If we need to remove data from the tree, we can create a
// new Merkle tree that omits the data we want to delete. Like with updating, we can
// then compare the old root hash with the new root hash to identify the differences.
// Similarly to updating data, direct deletion of data is not possible in a Merkle tree
// due to its immutable nature. If we need to remove data from the tree, we can create a
// new Merkle tree that omits the data we want to delete. Like with updating, we can
// then compare the old root hash with the new root hash to identify the differences.

void MerkleTree::deleteDataMerkleTree(const std::string& targetData) {
    std::string newNullData;
    updateMerkleTreeHelper(root, targetData, newNullData);
}
