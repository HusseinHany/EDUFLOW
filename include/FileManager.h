#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <map>
#include <string>
#include "Course.h"
#include "Student.h"

// ============ FILE MANAGER CLASS ============
class FileManager {
public:
    static void saveCourses(const std::vector<Course*>& courses, const std::string& filename = "data/courses.txt");
    static std::vector<Course*> loadCourses(const std::string& filename = "data/courses.txt");
    static void saveAllStudents(const std::map<int, Student*>& students);
    static std::map<int, Student*> loadAllStudents();
    static void createDataDirectory();
};

#endif // FILEMANAGER_H
