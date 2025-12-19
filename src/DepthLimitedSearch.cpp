#include "DepthLimitedSearch.h"

using namespace std;

DepthLimitedSearch::DepthLimitedSearch(Graph* g, map<int, Course*>* cm) : graph(g), courseMap(cm) {}

void DepthLimitedSearch::generatePathRecursive(int courseId, int depth, int limit, vector<int>& path,
    map<int, bool>& visited, vector<int>& completedCourses) {
    if (depth > limit || path.size() >= 10) return;

    if (!visited[courseId] && graph->canTakeCourse(courseId, completedCourses)) {
        visited[courseId] = true;
        path.push_back(courseId);
        completedCourses.push_back(courseId);

        for (int nextId : graph->getNextCourses(courseId)) {
            if (!visited[nextId]) {
                generatePathRecursive(nextId, depth + 1, limit, path, visited, completedCourses);
            }
        }
    }
}

vector<int> DepthLimitedSearch::generateLimitedPath(int startId, int depthLimit, vector<int>& completedCourses) {
    vector<int> path;
    map<int, bool> visited;

    for (int id : completedCourses) visited[id] = true;

    generatePathRecursive(startId, 0, depthLimit, path, visited, completedCourses);
    return path;
}
