#ifndef PATHSTACK_H
#define PATHSTACK_H

#include <stack>
#include <vector>

// ============ PATH STACK CLASS ============
class PathStack {
private:
    std::stack<int> pathStack;
    std::vector<int> currentPath;

public:
    void push(int courseId);
    int pop();
    bool isEmpty();
    std::vector<int> getPath();
    void clear();
};

#endif // PATHSTACK_H
