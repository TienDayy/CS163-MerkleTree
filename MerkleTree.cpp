#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MerkleTree {
   public:
    struct Node {
        string data;
        Node* left;
        Node* right;
        Node(const string& data) : data(data), left(nullptr), right(nullptr) {}
    };
    MerkleTree(const string& data) { root = new Node(data); }

   private:
    Node* root;

   public:
    // void buildMerkleTree(vector<string> leaves);
};
int main() { return 0; }