#include <iostream>
#include <queue>
#include <stack>
#include "BST.h"
using namespace std;

/**
 * Task 1: Define the structure for the Node and the BST
 *
 * An unbalanced binary tree is a type of binary tree where the heights of the two child subtrees of any node differ by more than one.
 *
 * Stick figure representation of an unbalanced binary tree:
 *
 *          10
 *         /  \
 *        5    15
 *         \     \
 *          8     20
 *                   \
 *                    25
 *
 * In this figure:
 * - The tree is unbalanced, with nodes skewed more towards the right.
 */

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    /** Task 2: Insert a node into the tree to form an unbalanced tree */
    void insert(int data) {
        root = insertRec(root, data);
    }

    Node* insertRec(Node* node, int data) {
        if (!node) return new Node(data);

        if (data < node->data) {
            node->left = insertRec(node->left, data);
        } else {
            node->right = insertRec(node->right, data);
        }

        return node;
    }

    /** Task 3: Remove a node from the tree */
    void remove(int data) {
        root = removeRec(root, data);
    }

    Node* removeRec(Node* node, int data) {
        if (!node) return nullptr;

        if (data < node->data) {
            node->left = removeRec(node->left, data);
        } else if (data > node->data) {
            node->right = removeRec(node->right, data);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    /** Helper function for in-order traversal recursively */
    void inorderRec(Node* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    /** Task 4: Perform an in-order traversal */
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    /** Helper function for pre-order traversal recursively */
    void preorderRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    /** Task 5: Perform a pre-order traversal */
    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    /** Helper function for post-order traversal recursively */
    void postorderRec(Node* node) {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    /** Task 6: Perform a post-order traversal */
    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    /** Helper function for BFS traversal iteratively */
    void bfsIter(Node* node) {
        if (!node) return;
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* current = q.front();
            cout << current->data << " ";
            q.pop();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
    }

    /** Task 7: Perform BFS iteratively */
    void bfsIter() {
        bfsIter(root);
        cout << endl;
    }

    /** Helper function for BFS traversal recursively */
    void bfsRec(queue<Node*> q) {
        if (q.empty()) return;
        Node* current = q.front();
        cout << current->data << " ";
        q.pop();
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
        bfsRec(q);
    }

    /** Task 8: Perform BFS recursively */
    void bfsRec() {
        queue<Node*> q;
        if (root) q.push(root);
        bfsRec(q);
        cout << endl;
    }

    /** Helper function for DFS traversal iteratively */
    void dfsIter(Node* node) {
        if (!node) return;
        stack<Node*> s;
        s.push(node);
        while (!s.empty()) {
            Node* current = s.top();
            cout << current->data << " ";
            s.pop();
            if (current->right) s.push(current->right);
            if (current->left) s.push(current->left);
        }
    }

    /** Task 9: Perform DFS iteratively */
    void dfsIter() {
        dfsIter(root);
        cout << endl;
    }

    /** Helper function for DFS traversal recursively */
    void dfsRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        dfsRec(node->left);
        dfsRec(node->right);
    }

    /** Task 10: Perform DFS recursively */
    void dfsRec() {
        dfsRec(root);
        cout << endl;
    }
};

int main() {
    BST unbalancedTree;
    unbalancedTree.insert(10);
    unbalancedTree.insert(5);
    unbalancedTree.insert(15);
    unbalancedTree.insert(8);
    unbalancedTree.insert(20);
    unbalancedTree.insert(25);

    BSTPrinter printer;
    printer.printTree(unbalancedTree.root);

    cout << "Unbalanced Binary Tree:\n";

    cout << "In-order Traversal: ";
    unbalancedTree.inorder();

    cout << "Pre-order Traversal: ";
    unbalancedTree.preorder();

    cout << "Post-order Traversal: ";
    unbalancedTree.postorder();

    cout << "BFS Iterative Traversal: ";
    unbalancedTree.bfsIter();

    cout << "BFS Recursive Traversal: ";
    unbalancedTree.bfsRec();

    cout << "DFS Iterative Traversal: ";
    unbalancedTree.dfsIter();

    cout << "DFS Recursive Traversal: ";
    unbalancedTree.dfsRec();

    unbalancedTree.remove(15);
    cout << "Updated Tree w/Removed Node 15: \n";
    printer.printTree(unbalancedTree.root);

    cout << "In-order Traversal after removing 15: ";
    unbalancedTree.inorder();

    return 0;
}
