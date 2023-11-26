#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;


/**
ERROR CODES:
- E1: Invalid input format
- E2: Duplicate pair
- E3: Parent has more than two children
- E4: Multiple roots
- E5: Input contains cycle

Return the FIRST error found in this order in case of multiple errors.
*/

/**
 * Returns the position of the character from A.
*/
int charPos(char c) {
    return int(c) - 65;
}

/**
 * Returns the character given the position from A.
*/
char charFromPos(int pos) {
    return char(pos + 65);
}

struct Node {
    Node* parent;
    Node* left;
    Node* right;

    int self;
};


void sExpression(Node* node) {
    cout << "(" << charFromPos(node->self);
    if (node->left != nullptr) {
        sExpression(node->left);
    }
    if (node->right != nullptr) {
        sExpression(node->right);
    }
    cout << ")";
}


int main() {
    // Get the input from stdin
    string line;
    std::getline(std::cin, line);

    /**
     * Create nodes with parents, left and right children, and character.
     * 
     * With checks:
     * E1 --> cannot parse input or no nodes were found
     * E2 --> child node already exists for node
     * E3 --> two children already exist for node
    */
    Node* foundNodes[26] {};
    bool foundOneNode = false;
    int firstParent;
    int errFlag = 0;
    for (int i = 1; i < line.length() - 1; i++) {
        if (line[i] == ',') {
            int self = charPos(line[i-1]);
            int child = charPos(line[i+1]);
            // If the character is outside range of A-Z, this is invalid input.
            if (self < 0 || self > 25 || child < 0 || child > 25) {
                errFlag = 1;
                break;
            }
            // If the self-child pair already was made, this is invalid input.
            if (errFlag == 0 && foundNodes[self] != nullptr) {
                if (
                    (foundNodes[self]->left != nullptr && foundNodes[self]->left->self == child) || 
                    (foundNodes[self]->right != nullptr && foundNodes[self]->right->self == child)
                ) {
                    errFlag = 2;
                }
            }
            // If the node doesn't exist, create it.
            if (foundNodes[self] == nullptr) {
                foundNodes[self] = new Node();
                foundNodes[self]->self = self;
            }
            // If the child doesn't exist, create it.
            if (foundNodes[child] == nullptr) {
                foundNodes[child] = new Node();
                foundNodes[child]->self = child;
            }
            // Assign the child to the parent's left or right child, prioritizing smallest for left.
            if (foundNodes[self]->left == nullptr) {
                foundNodes[self]->left = foundNodes[child];
            } else if (foundNodes[self]->right == nullptr) {
                if (foundNodes[self]->left->self > child) {
                    foundNodes[self]->right = foundNodes[self]->left;
                    foundNodes[self]->left = foundNodes[child];
                } else {
                    foundNodes[self]->right = foundNodes[child];
                }
            // If both children exist, this is invalid input.
            } else if (errFlag == 0) {
                errFlag = 3;
            }
            // Assign the child's parent to self
            foundNodes[child]->parent = foundNodes[self];
            foundOneNode = true;
            firstParent = self;
        }
    }
    if (!foundOneNode && errFlag == 0) {
        errFlag = 1;
    }
    if (errFlag != 0) {
        cout << "E" << errFlag << endl;
        return 0;
    }

    /**
     * Check:
     * E4 --> more than one node without parent means two roots
    */
    int rootCount = 0;
    for (Node* node : foundNodes) {
        if (node != nullptr && node->parent == nullptr) {
            rootCount++;
        }
    }
    if (rootCount > 1) {
        cout << "E4" << endl;
        return 0;
    }

    /**
     * Find the first node by tracing back to the top parent until one doesn't exist.
     * 
     * With checks:
     * E5 --> reach starting node during trace to root
    */
    Node* currentNode = foundNodes[firstParent];
    while (currentNode->parent != nullptr && currentNode->parent->self != firstParent) {
        currentNode = currentNode->parent;
    }
    if (currentNode->parent != nullptr) {
        cout << "E5" << endl;
        return 0;
    }

    /**
     * Perform depth-first search to construct S-Expression.
     * Always take left child first which is already arranged alphabetically.
    */
    sExpression(currentNode);

    return 0;
}