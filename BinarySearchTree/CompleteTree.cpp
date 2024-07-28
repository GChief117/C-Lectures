#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/**
 * Task 1: Define the structure for the Node and the BST
 *
 * A complete binary tree is a type of binary tree in which all the levels are completely filled except possibly for the last level,
 * which is filled from left to right.
 *
 * Stick figure representation of a complete binary tree:
 *
 *          1
 *        /   \
 *       2     3
 *      / \   / 
 *     4   5 6   
 *
 * In this figure:
 * - Node `1` has two children: `2` and `3`.
 * - Node `2` has two children: `4` and `5`.
 * - Node `3` has one child: `6`.
 * - Nodes `4`, `5`, and `6` are leaves and do not have any children.
 *
 * A complete binary tree will have this structure where all levels are completely filled except possibly for the last level,
 * which is filled from left to right.
 */

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    /** Task 2: Insert a node into the tree */
    void insert(int data) {
        if (!root) {
            root = new Node(data);
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (!current->left) {
                current->left = new Node(data);
                return;
            } else {
                q.push(current->left);
            }
            if (!current->right) {
                current->right = new Node(data);
                return;
            } else {
                q.push(current->right);
            }
        }
    }

    /** Task 3: Remove a node from the tree */
    void remove(int data) {
        if (!root) return;

        queue<Node*> q;
        q.push(root);
        Node* target = nullptr;
        Node* parent = nullptr;
        Node* current = nullptr;

        while (!q.empty()) {
            current = q.front();
            q.pop();
            if (current->data == data) {
                target = current;
            }
            if (current->left) {
                q.push(current->left);
                parent = current;
            }
            if (current->right) {
                q.push(current->right);
                parent = current;
            }
        }

        if (!target) return;

        if (current != target) {
            target->data = current->data;
            if (parent->left == current) {
                delete parent->left;
                parent->left = nullptr;
            } else {
                delete parent->right;
                parent->right = nullptr;
            }
        } else {
            delete root;
            root = nullptr;
        }
    }

    /** Task 4: Perform an in-order traversal */
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    void inorderRec(Node* node) {
        if (!node) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    /** Task 5: Perform a pre-order traversal */
    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    void preorderRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    /** Task 6: Perform a post-order traversal */
    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    void postorderRec(Node* node) {
        if (!node) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    /** Task 7: Perform BFS iteratively */
    void bfsIter() {
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* current = q.front();
            cout << current->data << " ";
            q.pop();
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }

    /** Task 8: Perform BFS recursively */
    void bfsRec(queue<Node*> q) {
        if (q.empty()) return;
        Node* current = q.front();
        cout << current->data << " ";
        q.pop();
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
        bfsRec(q);
    }

    void bfsRec() {
        queue<Node*> q;
        if (root) q.push(root);
        bfsRec(q);
        cout << endl;
    }

    /** Task 9: Perform DFS iteratively */
    void dfsIter() {
        if (!root) return;
        stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* current = s.top();
            cout << current->data << " ";
            s.pop();
            if (current->right) s.push(current->right);
            if (current->left) s.push(current->left);
        }
        cout << endl;
    }

    /** Task 10: Perform DFS recursively */
    void dfsRec(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        dfsRec(node->left);
        dfsRec(node->right);
    }

    void dfsRec() {
        dfsRec(root);
        cout << endl;
    }
};

int main() {
    BST completeTree;
    completeTree.insert(1);
    completeTree.insert(2);
    completeTree.insert(3);
    completeTree.insert(4);
    completeTree.insert(5);
    completeTree.insert(6);

    cout << "Complete Binary Tree:\n";

    cout << "In-order Traversal: ";
    completeTree.inorder();

    cout << "Pre-order Traversal: ";
    completeTree.preorder();

    cout << "Post-order Traversal: ";
    completeTree.postorder();

    cout << "BFS Iterative Traversal: ";
    completeTree.bfsIter();

    cout << "BFS Recursive Traversal: ";
    completeTree.bfsRec();

    cout << "DFS Iterative Traversal: ";
    completeTree.dfsIter();

    cout << "DFS Recursive Traversal: ";
    completeTree.dfsRec();

    completeTree.remove(3);

    cout << "In-order Traversal after removing 3: ";
    completeTree.inorder();

    return 0;
}
