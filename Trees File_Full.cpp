//Insert a Node From a Balanced Tree

#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include "TreePrinter.h"
using namespace std;

class AVLTree {
public:
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
        Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
    };
    
    Node* root;
    AVLTree() : root(nullptr) {}
    
    //height
    int height(Node* node) {
        return node ? node->height : 0;
    }
    //get a balance
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }
    
    //check the right side for insertion
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }
    
    //check the left side for insertion
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }
    
    //insert the node
    Node* insert(Node* node, int key) {
        if(!node) return new Node(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        else {
            return node;
        }
        
        //check the height
        node->height = 1 + max(height(node->left), height(node->right));
        
        //get the balance
        int balance = getBalance(node);
        
        //check the balance of the tree
        if (balance > 1 && key < node->left->key){
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
        if (balance > 1 && key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }
    
    //removing a node
    //min value holder, to check the current node
    Node* minValueNode(Node* node) {
        Node* current = node;
        while(current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    
    //delete the node
    Node* deleteNode(Node* root, int key){
        if (!root) return root;
        
        if (key < root->key){
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        }
        else {
            if ((root->left == nullptr) || (root->right == nullptr)){
                Node* temp = root->left ? root-> left : root->right;
                if(!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        
        if (!root) return root;
        
        //check the height
        root->height = 1 + max(height(root->left), height(root->right));
        
        int balance = getBalance(root);
        
        //check the balance of the tree
        if (balance > 1 && key < root->left->key){
            return rightRotate(root);
        }
        if (balance < -1 && key > root->right->key) {
            return leftRotate(root);
        }
        if (balance > 1 && key > root->left->key){
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && key < root->right->key){
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    
    //inorder traversal
    void inorder(Node* root){
        if (root) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }
    
    //pre-order traversal
    void preorder(Node* root) {
        if (root){
            cout << root->key << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }
    
    
    //post order traversal
    void postorder(Node* root){
        if (root){
            postorder(root->left);
            postorder(root->right);
            cout << root->key << " ";
        }
    }
    
    //BFS-Breadth First Search
    void bfs(Node* root){
        //uses a queue
        if (!root) return;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()){
            Node* node = q.front();
            cout << node->key << " ";
            q.pop();
            if (node->left){
                q.push(node->left);
            }
            if (node->right){
                q.push(node->right);
            }
        }
    }
    
    //DFS-Depth First Search--Uses a Stack to keep track
    //Focusing on the depth
    void dfs(Node* root){
        if (!root) return;
        stack<Node*> s;
        s.push(root);
        while(!s.empty()){
            Node* node = s.top();
            cout << node->key << " ";
            s.pop();
            if(node->right){
                s.push(node->right);
            }
            if(node->left){
                s.push(node->left);
            }
        }
    }

};

int main(){
    AVLTree avl;
    TreePrinter printer;
    avl.root = avl.insert(avl.root, 10);
    avl.root = avl.insert(avl.root, 20);
    avl.root = avl.insert(avl.root, 30);
    cout << "Nodes inserted into AVL Tree" << endl;
    printer.printPretty(avl.root, 1, 0);
    
    cout << "In Order Traversal: " << endl;
    avl.inorder(avl.root);
    
    cout << "\nPre-Order Traversal: " << endl;
    avl.preorder(avl.root);
    
    cout << "\nPost-Order Traversal: " << endl;
    avl.postorder(avl.root);
    
    cout << "\nBFS of AVL Balanced Tree:" << endl;
    avl.bfs(avl.root);
    
    cout << "\nDFS of AVL Balanced Tree:" << endl;
    avl.dfs(avl.root);
    
    
    avl.root = avl.deleteNode(avl.root, 20);
    cout << "\nSelected node has been removed from the tree" << endl;
    printer.printPretty(avl.root, 1, 0);
    return 0;
}



Unblanced Tree:
#include <iostream>
#include <queue>
#include <stack>
#include "TreePrinter.h"

using namespace std;

class BinaryTree{
public:
    struct Node{
        int key;
        Node* left;
        Node* right;
        Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    BinaryTree() : root(nullptr) {}
    
    //Insert
    Node* insert(Node* node, int key){
        if(!node) return new Node(key);
        
        if(key < node->key){
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }
        return node;
    }
    
    
    //removing a node
    //check with the current node
    Node* minValueNode(Node* node){
        Node* current = node;
        while (current && current->left != nullptr){
            current = current->left;
        }
        return current;
    }
    
    //we will delete a node
    Node* deleteNode(Node* root, int key){
        if (!root) return root;
        
        if(key < root->key){
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->key){
            root->right = deleteNode(root->right, key);
        }
        else {
            if(root->left == nullptr){
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr){
                Node* temp = root->left;
                delete root;
                return temp;
            }
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
        return root;
    }
    
    //inorder traversal
    void inorder(Node* root){
        if (root){
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }
    
    //pre-order traversal
    void preorder(Node* root){
        if (root) {
            cout << root->key << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }
    
    //post order traversal
    void postorder(Node* root){
        if(root){
            postorder(root->left);
            postorder(root->right);
            cout << root->key << " ";
        }
    }
    
    //BFS-Use a Queue
    void bfs(Node* root){
        if (!root) return;
        queue<Node*> q;
        q.push (root);
        while (!q.empty()){
            Node* node = q.front();
            cout << node->key << " ";
            q.pop();
            if (node->left) {
                q.push(node->left);
            }
            if (node->right) {
                q.push(node->right);
            }
        }
    }
    
    //DFS--Use a Stack
    void dfs(Node* root){
        if (!root) return;
        stack<Node*> s;
        s.push(root);
        while(!s.empty()){
            Node* node = s.top();
            cout << node->key << " ";
            s.pop();
            if (node->right){
                s.push(node->right);
            }
            if (node->left){
                s.push(node->left);
            }
        }
    }
};

int main(){
    BinaryTree bt;
    TreePrinter printer;
    bt.root = bt.insert(bt.root, 10);
    bt.root = bt.insert(bt.root, 20);
    bt.root = bt.insert(bt.root, 5);
    cout << "Nodes inserted in the unbalanced tree: " << endl;
    printer.printPretty(bt.root, 1, 0);
    
    //output our in-order traversal
    cout << "In-order traversal of unbalanced tree: ";
    bt.inorder(bt.root);
    
    //output our pre-order traversal
    cout << "\nPre-order traversal of unbalanced tree: ";
    bt.preorder(bt.root);
    
    //output our post-order traversal
    cout << "\nPost-order traversal of unbalanced tree: ";
    bt.postorder(bt.root);

    //BFS
    cout << "\nBFS of unbalanced tree: ";
    bt.bfs(bt.root);
    
    //DFS
    cout << "\nDFS of unbalanced tree: ";
    bt.dfs(bt.root);
    
    bt.root = bt.deleteNode(bt.root, 20);
    cout << "\nNodes deleted from the unbalanced tree: " << endl;
    printer.printPretty(bt.root, 1, 0);

    return 0;
}
