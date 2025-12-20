#include "AVLTree.h"

using namespace std;

// ============ AVL TREE NODE ============
AVLNode::AVLNode(Course* c) : course(c), left(nullptr), right(nullptr), height(1) {}

// ============ AVL TREE CLASS ============
AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() { deleteTree(root); }

int AVLTree::getHeight(AVLNode* node) { return node ? node->height : 0; }

int AVLTree::getBalance(AVLNode* node) { 
    return node ? getHeight(node->left) - getHeight(node->right) : 0; 
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node) node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

AVLNode* AVLTree::insertRecursive(AVLNode* node, Course* course) {
    if (!node) return new AVLNode(course);

    if (course->aiScore < node->course->aiScore)
        node->left = insertRecursive(node->left, course);
    else if (course->aiScore > node->course->aiScore)
        node->right = insertRecursive(node->right, course);
    else
        return node;

    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1 && course->aiScore < node->left->course->aiScore)
        return rotateRight(node);
    if (balance < -1 && course->aiScore > node->right->course->aiScore)
        return rotateLeft(node);
    if (balance > 1 && course->aiScore > node->left->course->aiScore) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && course->aiScore < node->right->course->aiScore) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVLTree::inorderTraversal(AVLNode* node, vector<Course*>& result) {
    if (!node) return;
    inorderTraversal(node->right, result);
    result.push_back(node->course);
    inorderTraversal(node->left, result);
}

void AVLTree::deleteTree(AVLNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void AVLTree::insert(Course* course) { root = insertRecursive(root, course); }

vector<Course*> AVLTree::getSortedCourses() {
    vector<Course*> result;
    inorderTraversal(root, result);
    return result;
}

void AVLTree::clear() {
    deleteTree(root);
    root = nullptr;
}
