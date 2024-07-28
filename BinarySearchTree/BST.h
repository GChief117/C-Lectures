//
//  BST.h
//  BinarySearchTrees
//
//  Created by Gunnar Beck on 7/28/24.
//

#ifndef BST_h
#define BST_h

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>

using namespace std;

// Node structure for the tree
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Define the class
class BSTPrinter {
public:
    // Function to print the tree
    void printTree(Node* root) const {
        if (root == nullptr) return;

        int h = height(root);
        int width = (1 << h) - 1; // Width of the tree at the bottom level
        vector<string> output(h * 2, string(width * 3, ' '));

        printTree(root, 0, 0, width, output);

        for (const auto& line : output) {
            cout << line << endl;
        }
    }

private:
    // Function to calculate the height of the tree
    int height(Node* root) const {
        if (root == nullptr) return 0;
        return max(height(root->left), height(root->right)) + 1;
    }

    // Helper function to print the tree
    void printTree(Node* node, int level, int left, int right, vector<string>& output) const {
        if (node == nullptr) return;
        
        int mid = (left + right) / 2;
        output[level][mid * 3] = '0' + node->data / 10;
        output[level][mid * 3 + 1] = '0' + node->data % 10;

        if (node->left) {
            int nextMid = (left + mid) / 2;
            output[level + 1][nextMid * 3 + 1] = '/';
            printTree(node->left, level + 2, left, mid, output);
        }

        if (node->right) {
            int nextMid = (mid + right) / 2;
            output[level + 1][nextMid * 3 - 1] = '\\';
            printTree(node->right, level + 2, mid, right, output);
        }
    }
};


#endif /* BST_h */
