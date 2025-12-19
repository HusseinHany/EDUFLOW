#include "PathStack.h"

using namespace std;

void PathStack::push(int courseId) {
    pathStack.push(courseId);
    currentPath.push_back(courseId);
}

int PathStack::pop() {
    if (!pathStack.empty()) {
        int courseId = pathStack.top();
        pathStack.pop();
        if (!currentPath.empty()) currentPath.pop_back();
        return courseId;
    }
    return -1;
}

bool PathStack::isEmpty() { return pathStack.empty(); }

vector<int> PathStack::getPath() { return currentPath; }

void PathStack::clear() {
    while (!pathStack.empty()) pathStack.pop();
    currentPath.clear();
}
