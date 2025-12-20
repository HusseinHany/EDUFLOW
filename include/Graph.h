#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>

// ============ GRAPH CLASS ============
class Graph {
private:
    std::map<int, std::vector<int>> adjList;
    std::map<int, std::vector<int>> prerequisites;

    bool hasCycleDFS(int node, std::map<int, int>& visited);

public:
    void addCourse(int courseId);
    void addPrerequisite(int courseId, int prereqId);
    bool hasCycle();
    bool canTakeCourse(int courseId, std::vector<int>& completedCourses);
    std::vector<int> getPrerequisites(int courseId);
    std::vector<int> getNextCourses(int courseId);
    void clear();
};

#endif // GRAPH_H
