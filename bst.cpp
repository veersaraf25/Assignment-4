#include <iostream>
using namespace std;

// Node definition for BST
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// BST class
class BST {
public:
    BSTNode* root;

    BST() : root(nullptr) {}

    // Print tree in a tree structure
    void printTree(BSTNode* root, string indent, bool last) {
        if (root) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "     ";
            } else {
                cout << "L----";
                indent += "|    ";
            }
            cout << root->data << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }
};
