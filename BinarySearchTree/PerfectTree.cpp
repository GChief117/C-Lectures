#include <iostream>
#include <queue>
#include <stack>
#include "BST.h"
using namespace std;

/**
 * Task 1: Define the structure for the Node and the BST
 *
 * A perfect binary tree is a type of binary tree in which all internal nodes have exactly two children,
 * and all leaf nodes are at the same level.
 *
 * Stick figure representation of a perfect binary tree:
 *
 *          1
 *        /   \
 *       2     3
 *      / \   / \
 *     4   5 6   7
 *
 * In this figure:
 * - Node `1` has exactly two children: `2` and `3`.
 * - Node `2` has exactly two children: `4` and `5`.
 * - Node `3` has exactly two children: `6` and `7`.
 * - All leaf nodes `4`, `5`, `6`, and `7` are at the same level.
 */

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    /** Task 2: Insert a node into the tree to form a perfect binary tree */
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
    BST perfectTree;
    perfectTree.insert(1);
    perfectTree.insert(2);
    perfectTree.insert(3);
    perfectTree.insert(4);
    perfectTree.insert(5);
    perfectTree.insert(6);
    perfectTree.insert(7);

    BSTPrinter printer;
    cout << "Perfect Binary Tree:\n";
    printer.printTree(perfectTree.root);

    cout << "In-order Traversal: ";
    perfectTree.inorder();

    cout << "Pre-order Traversal: ";
    perfectTree.preorder();

    cout << "Post-order Traversal: ";
    perfectTree.postorder();

    cout << "BFS Iterative Traversal: ";
    perfectTree.bfsIter();

    cout << "BFS Recursive Traversal: ";
    perfectTree.bfsRec();

    cout << "DFS Iterative Traversal: ";
    perfectTree.dfsIter();

    cout << "DFS Recursive Traversal: ";
    perfectTree.dfsRec();

    perfectTree.remove(3);
    cout << "Updated Tree w/Removed Node 3: \n";
    printer.printTree(perfectTree.root);

    cout << "In-order Traversal after removing 3: ";
    perfectTree.inorder();

    return 0;
}
