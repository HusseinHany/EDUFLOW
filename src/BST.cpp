#include "BST.h"

using namespace std;

// ============ BST NODE ============
BSTNode::BSTNode(int k, Course* c) : key(k), course(c), left(nullptr), right(nullptr) {}

// ============ BST CLASS ============
BST::BST() : root(nullptr) {}

BST::~BST() { deleteTree(root); }

BSTNode* BST::insertRecursive(BSTNode* node, int key, Course* course) {
    if (!node) return new BSTNode(key, course);
    if (key < node->key) node->left = insertRecursive(node->left, key, course);
    else if (key > node->key) node->right = insertRecursive(node->right, key, course);
    return node;
}

Course* BST::searchRecursive(BSTNode* node, int key) {
    if (!node) return nullptr;
    if (key == node->key) return node->course;
    if (key < node->key) return searchRecursive(node->left, key);
    return searchRecursive(node->right, key);
}

void BST::deleteTree(BSTNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insert(int key, Course* course) { root = insertRecursive(root, key, course); }

Course* BST::search(int courseId) { return searchRecursive(root, courseId); }

void BST::clear() {
    deleteTree(root);
    root = nullptr;
}
