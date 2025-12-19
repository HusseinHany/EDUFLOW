#include "Graph.h"
#include <algorithm>

using namespace std;

bool Graph::hasCycleDFS(int node, map<int, int>& visited) {
    visited[node] = 1;
    for (int neighbor : adjList[node]) {
        if (visited[neighbor] == 1) return true;
        if (visited[neighbor] == 0 && hasCycleDFS(neighbor, visited)) return true;
    }
    visited[node] = 2;
    return false;
}

void Graph::addCourse(int courseId) {
    if (adjList.find(courseId) == adjList.end()) {
        adjList[courseId] = vector<int>();
        prerequisites[courseId] = vector<int>();
    }
}

void Graph::addPrerequisite(int courseId, int prereqId) {
    prerequisites[courseId].push_back(prereqId);
    adjList[prereqId].push_back(courseId);
}

bool Graph::hasCycle() {
    map<int, int> visited;
    for (auto& pair : adjList) {
        if (visited[pair.first] == 0) {
            if (hasCycleDFS(pair.first, visited)) return true;
        }
    }
    return false;
}

bool Graph::canTakeCourse(int courseId, vector<int>& completedCourses) {
    for (int prereq : prerequisites[courseId]) {
        if (find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) {
            return false;
        }
    }
    return true;
}

vector<int> Graph::getPrerequisites(int courseId) { return prerequisites[courseId]; }

vector<int> Graph::getNextCourses(int courseId) { return adjList[courseId]; }

void Graph::clear() {
    adjList.clear();
    prerequisites.clear();
}
