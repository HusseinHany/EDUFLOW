#ifndef BST_H
#define BST_H

#include "Course.h"

// ============ BST NODE ============
class BSTNode {
public:
    int key;
    Course* course;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int k, Course* c);
};

// ============ BST CLASS ============
class BST {
private:
    BSTNode* root;

    BSTNode* insertRecursive(BSTNode* node, int key, Course* course);
    Course* searchRecursive(BSTNode* node, int key);
    void deleteTree(BSTNode* node);

public:
    BST();
    ~BST();
    
    void insert(int key, Course* course);
    Course* search(int courseId);
    void clear();
};

#endif // BST_H
