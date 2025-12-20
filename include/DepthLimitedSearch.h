#ifndef DEPTHLIMITEDSEARCH_H
#define DEPTHLIMITEDSEARCH_H

#include <vector>
#include <map>
#include "Graph.h"
#include "Course.h"

// ============ DEPTH LIMITED SEARCH CLASS ============
class DepthLimitedSearch {
private:
    Graph* graph;
    std::map<int, Course*>* courseMap;

    void generatePathRecursive(int courseId, int depth, int limit, std::vector<int>& path,
        std::map<int, bool>& visited, std::vector<int>& completedCourses);

public:
    DepthLimitedSearch(Graph* g, std::map<int, Course*>* cm);
    
    std::vector<int> generateLimitedPath(int startId, int depthLimit, std::vector<int>& completedCourses);
};

#endif // DEPTHLIMITEDSEARCH_H
