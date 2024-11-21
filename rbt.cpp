#include <iostream>
#include <iomanip>
using namespace std;
 
enum COLOR { RED, BLACK };
 
class RBTNode {
public:
    int val;
    COLOR color;
    RBTNode *left, *right, *parent;
    
    RBTNode(int val) : val(val) {
        parent = left = right = NULL;
        color = RED;
    }
};
    
class RBTree {
public:
    RBTNode *root;

    void printTreeHelper(RBTNode* node, int indent = 0, bool isLeft = false) {
        if (node == nullptr)
            return;

        indent += 4;
        printTreeHelper(node->right, indent, false);

        cout << std::setw(indent);
        if (node->parent == nullptr)
            cout << "Root ";
        else if (isLeft)
            cout << "L----";
        else
            cout << "R----";

        string sColor = (node->color == BLACK) ? "BLACK" : "RED";
        cout << node->val << "(" << sColor << ")" << endl;

        printTreeHelper(node->left, indent, true);
    };

    void printTree() {
        printTreeHelper(root);
    }
};
