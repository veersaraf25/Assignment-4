include  <iostream>
#include <iomanip>
#include <utility>
#include <vector>
using namespace std;

enum COLOR { RED, BLACK };

class RBTNode {
public:
    int val;
    COLOR color;
    RBTNode *left, *right, *parent;

    RBTNode(int val) : val(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
public:
    RBTNode *root;

    RBTree() : root(nullptr) {}

    RBTNode* bstInsert(RBTNode* root, RBTNode* newNode) {
        if (!root)
            return newNode;

        if (newNode->val < root->val) {
            root->left = bstInsert(root->left, newNode);
            root->left->parent = root;
        } else {
            root->right = bstInsert(root->right, newNode);
            root->right->parent = root;
        }

        return root;
    }

    void insert(int val) {
        RBTNode* newNode = new RBTNode(val);
        root = bstInsert(root, newNode);
        fixInsert(newNode);
    }

    void fixInsert(RBTNode* node) {
        while (node != root && node->parent->color == RED) {
            RBTNode* parent = node->parent;
            RBTNode* grandparent = parent->parent;

            if (parent == grandparent->left) {
                RBTNode* uncle = grandparent->right;

                if (uncle && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                }
            } else {
                RBTNode* uncle = grandparent->left;

                if (uncle && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                }
            }
        }
        root->color = BLACK;
    }

    void rotateLeft(RBTNode* node) {
        RBTNode* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left)
            rightChild->left->parent = node;

        rightChild->parent = node->parent;

        if (!node->parent)
            root = rightChild;
        else if (node == node->parent->left)
            node->parent->left = rightChild;
        else
            node->parent->right = rightChild;

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(RBTNode* node) {
        RBTNode* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right)
            leftChild->right->parent = node;

        leftChild->parent = node->parent;

        if (!node->parent)
            root = leftChild;
        else if (node == node->parent->left)
            node->parent->left = leftChild;
        else
            node->parent->right = leftChild;

        leftChild->right = node;
        node->parent = leftChild;
    }

    bool search(int val) {
        RBTNode* current = root;
        while (current) {
            if (current->val == val)
                return true;
            current = (val < current->val) ? current->left : current->right;
        }
        return false;
    }

    pair<RBTree, RBTree> split(int key) {
        RBTree T1, T2;
        splitHelper(root, key, T1, T2);
        return {T1, T2};
    }

    void splitHelper(RBTNode* node, int key, RBTree& T1, RBTree& T2) {
        if (!node)
            return;

        if (node->val <= key) {
            T1.insert(node->val);
            splitHelper(node->left, key, T1, T2);
            splitHelper(node->right, key, T1, T2);
        } else {
            T2.insert(node->val);
            splitHelper(node->left, key, T1, T2);
            splitHelper(node->right, key, T1, T2);
        }
    }

    RBTree* merge(RBTree& tree2) {
        vector<int> elements;
        collectElements(root, elements);
        collectElements(tree2.root, elements);

        sort(elements.begin(), elements.end());

        RBTree* mergedTree = new RBTree();
        for (int val : elements) {
            mergedTree->insert(val);
        }
        return mergedTree;
    }

    void collectElements(RBTNode* node, vector<int>& elements) {
        if (!node) return;
        collectElements(node->left, elements);
        elements.push_back(node->val);
        collectElements(node->right, elements);
    }

    void printTreeHelper(RBTNode* node, int indent = 0, bool isLeft = false) {
        if (!node)
            return;

        indent += 4;
        printTreeHelper(node->right, indent, false);

        cout << setw(indent);
        if (!node->parent)
            cout << "Root ";
        else
            cout << (isLeft ? "L----" : "R----");

        cout << node->val << "(" << (node->color == BLACK ? "BLACK" : "RED") << ")" << endl;

        printTreeHelper(node->left, indent, true);
    }

    void printTree() {
        if (!root) {
            cout << "The tree is empty." << endl;
        } else {
            printTreeHelper(root);
        }
    }
