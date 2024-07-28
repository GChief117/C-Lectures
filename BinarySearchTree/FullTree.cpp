#include <iostream>
#include <queue>
#include <stack>
#include "BST.h"
using namespace std;

/**
 * Task 1: Define the structure for the Node and the BST
 *
 * A full binary tree is a type of binary tree in which every node other than the leaves has exactly two children.
 *
 * Stick figure representation of a full binary tree:
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
 * - Nodes `4`, `5`, `6`, and `7` are leaves and do not have any children.
 *
 * A full binary tree will have this structure where every non-leaf node has exactly two children.
 */


class BST {
public:
    Node* root;

    /** Helper function to insert a node recursively */
    Node* insertRec(Node* node, int data) {
        // Step: If the node is null, create a new node
        if (!node) return new Node(data);

        // Step: Otherwise, recurse down the tree
        if (data < node->data)
            node->left = insertRec(node->left, data);
        else
            node->right = insertRec(node->right, data);
        
        return node;
    }

    /** Helper function to remove a node recursively */
    Node* removeRec(Node* node, int data) {
        // Step: If the node is null, return null
        if (!node) return nullptr;

        // Step: Find the node to be removed
        if (data < node->data) {
            node->left = removeRec(node->left, data);
        } else if (data > node->data) {
            node->right = removeRec(node->right, data);
        } else {
            // Step: Node with only one child or no child
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Step: Node with two children, get the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRec(node->right, temp->data);
        }
        return node;
    }

    /** Helper function to find the minimum value node */
    Node* minValueNode(Node* node) {
        // Step: Find the leftmost leaf
        Node* current = node;
        while (current && current->left != nullptr)
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

    /** Helper function for pre-order traversal recursively */
    void preorderRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    /** Helper function for post-order traversal recursively */
    void postorderRec(Node* node) {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
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

    /** Helper function for DFS traversal recursively */
    void dfsRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        dfsRec(node->left);
        dfsRec(node->right);
    }

public:
    BST() : root(nullptr) {}

    /** Task 2: Insert a node into the tree */
    void insert(int data) {
        root = insertRec(root, data);
    }

    /** Task 3: Remove a node from the tree */
    void remove(int data) {
        root = removeRec(root, data);
    }

    /** Task 4: Perform an in-order traversal */
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    /** Task 5: Perform a pre-order traversal */
    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    /** Task 6: Perform a post-order traversal */
    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    /** Task 7: Perform BFS iteratively */
    void bfsIter() {
        bfsIter(root);
        cout << endl;
    }

    /** Task 8: Perform BFS recursively */
    void bfsRec() {
        queue<Node*> q;
        q.push(root);
        bfsRec(q);
        cout << endl;
    }

    /** Task 9: Perform DFS iteratively */
    void dfsIter() {
        dfsIter(root);
        cout << endl;
    }

    /** Task 10: Perform DFS recursively */
    void dfsRec() {
        dfsRec(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(3);
    tree.insert(7);
    tree.insert(15);
    tree.insert(25);
    
    BSTPrinter printer;
    printer.printTree(tree.root);

    cout << "In-order Traversal: ";
    tree.inorder();

    cout << "Pre-order Traversal: ";
    tree.preorder();

    cout << "Post-order Traversal: ";
    tree.postorder();

    cout << "BFS Iterative Traversal: ";
    tree.bfsIter();

    cout << "BFS Recursive Traversal: ";
    tree.bfsRec();

    cout << "DFS Iterative Traversal: ";
    tree.dfsIter();

    cout << "DFS Recursive Traversal: ";
    tree.dfsRec();

    tree.remove(20);

    cout << "In-order Traversal after removing 20: ";
    tree.inorder();

    return 0;
}

