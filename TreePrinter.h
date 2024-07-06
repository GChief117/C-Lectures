#ifndef TREEPRINTER_H
#define TREEPRINTER_H

#include <iostream>
#include <iomanip>
#include <deque>
#include <cmath>
#include <string>

using namespace std;

class TreePrinter {
public:
    template <typename Node>
    int height(Node* root) {
        if (root == nullptr) return 0;
        return 1 + max(height(root->left), height(root->right));
    }

    template <typename Node>
    void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue) {
        typename deque<Node*>::const_iterator iter = nodesQueue.begin();
        for (int i = 0; i < nodesInThisLevel / 2; i++) {
            cout << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
            cout << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
        }
        cout << endl;
    }

    template <typename Node>
    void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node*>& nodesQueue) {
        typename deque<Node*>::const_iterator iter = nodesQueue.begin();
        for (int i = 0; i < nodesInThisLevel; i++, iter++) {
            cout << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
            cout << setw(branchLen + 2) << ((*iter) ? to_string((*iter)->key) : "");
            cout << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
        }
        cout << endl;
    }

    template <typename Node>
    void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node*>& nodesQueue) {
        typename deque<Node*>::const_iterator iter = nodesQueue.begin();
        for (int i = 0; i < nodesInThisLevel; i++, iter++) {
            cout << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? to_string((*iter)->key) : "");
        }
        cout << endl;
    }

    template <typename Node>
    void printPretty(Node* root, int level, int indentSpace) {
        int h = height(root);
        int nodesInThisLevel = 1;

        int branchLen = 2 * ((int)pow(2.0, h) - 1) - (3 - level) * (int)pow(2.0, h - 1);
        int nodeSpaceLen = 2 + (level + 1) * (int)pow(2.0, h);
        int startLen = branchLen + (3 - level) + indentSpace;

        deque<Node*> nodesQueue;
        nodesQueue.push_back(root);
        for (int r = 1; r < h; r++) {
            printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
            branchLen = branchLen / 2 - 1;
            nodeSpaceLen = nodeSpaceLen / 2 + 1;
            startLen = branchLen + (3 - level) + indentSpace;
            printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);

            for (int i = 0; i < nodesInThisLevel; i++) {
                Node* currNode = nodesQueue.front();
                nodesQueue.pop_front();
                if (currNode) {
                    nodesQueue.push_back(currNode->left);
                    nodesQueue.push_back(currNode->right);
                } else {
                    nodesQueue.push_back(nullptr);
                    nodesQueue.push_back(nullptr);
                }
            }
            nodesInThisLevel *= 2;
        }
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
        printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue);
    }
};

#endif // TREEPRINTER_H