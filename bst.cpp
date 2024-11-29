#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BSTNode* root;

    BST() : root(nullptr) {}

    BSTNode* insert(BSTNode* node, int val) {
        if (node == nullptr) {
            return new BSTNode(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    bool search(BSTNode* node, int val) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == val) {
            return true;
        } else if (val < node->data) {
            return search(node->left, val);
        } else {
            return search(node->right, val);
        }
    }

    bool search(int val) {
        return search(root, val);
    }

    BSTNode* constructBSTFromPreorderUtil(vector<int>& preorder, int& index, int min, int max) {
        if (index >= preorder.size()) {
            return nullptr;
        }

        int val = preorder[index];
        if (val < min || val > max) {
            return nullptr;
        }

        BSTNode* node = new BSTNode(val);
        index++;

        node->left = constructBSTFromPreorderUtil(preorder, index, min, val - 1);
        node->right = constructBSTFromPreorderUtil(preorder, index, val + 1, max);

        return node;
    }

    BSTNode* constructBSTFromPreorder(vector<int>& preorder) {
        if (preorder.empty()) {
            return nullptr;
        }
        int index = 0;
        return constructBSTFromPreorderUtil(preorder, index, INT_MIN, INT_MAX);
    }

    BSTNode* findLCA(BSTNode* node, int n1, int n2) {
        if (node == nullptr) {
            return nullptr;
        }

        if (n1 < node->data && n2 < node->data) {
            return findLCA(node->left, n1, n2);
        }

        if (n1 > node->data && n2 > node->data) {
            return findLCA(node->right, n1, n2);
        }

        return node;
    }

    BSTNode* findLCA(int n1, int n2) {
        if (!search(n1) || !search(n2)) {
            return nullptr;
        }
        return findLCA(root, n1, n2);
    }

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

    void printTree() {
        if (root == nullptr) {
            cout << "The tree is empty." << endl;
        } else {
            printTree(root, "", true);
        }
    }
