#include <functional>
#include <iostream>
#include <string>
#include <vector>

class MerkleTree {
   public:
    struct Node {
        std::string key;
        Node* left;
        Node* right;
        Node() : key(""), left(nullptr), right(nullptr) {}
    };
    MerkleTree() {
        root = new Node();
        height = 0;
    }
    ~MerkleTree() { deleteMerkleTree(); }

   private:
    Node* root;
    std::string calculate_hash(const std::string&);
    void buildMerkleTreeHelper(Node*, int, std::vector<std::string>);
    bool searchInMerkleTreeHelper(Node*, const std::string&);
    void deleteMerkleTreeHelper(Node*);
    void deleteMerkleTree() { deleteMerkleTreeHelper(root); }

   public:
    int height;
    int getHeight(int);
    void buildMerkleTree(const std::vector<std::string>&);
    bool searchInMerkleTree(const std::string&);
};
