#ifndef AVLTREE_H
#define AVLTREE_H

#include <vector>
#include <algorithm>
#include "Course.h"

// ============ AVL TREE NODE ============
class AVLNode {
public:
    Course* course;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Course* c);
};

// ============ AVL TREE CLASS ============
class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    void updateHeight(AVLNode* node);
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    AVLNode* insertRecursive(AVLNode* node, Course* course);
    void inorderTraversal(AVLNode* node, std::vector<Course*>& result);
    void deleteTree(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();
    
    void insert(Course* course);
    std::vector<Course*> getSortedCourses();
    void clear();
};

#endif // AVLTREE_H
