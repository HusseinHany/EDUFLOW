#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <map>
#include "Enumerations.h"
#include "LinkedList.h"
#include "WeeklySchedule.h"
#include "ProgressReport.h"

// ============ STUDENT CLASS ============
class Student {
public:
    int id;
    std::string name;
    std::string email;
    SkillLevel skillLevel;
    std::string learningGoal;
    int availableHours;
    std::vector<int> completedCourses;
    LinkedList completedHistory;
    std::map<std::string, int> skills;
    WeeklySchedule schedule;
    int stressLevel;
    std::vector<std::string> concerns;
    std::string mentalHealthNote;

    Student();
    Student(int i, std::string n, std::string e, SkillLevel level, std::string goal, int hours);
    
    void completeCourse(int courseId, std::string courseName, double score, std::vector<std::string>& courseSkills);
    void displayProfile();
    ProgressReport generateReport(int totalCourses);
    void saveToFile(const std::string& filename);
    static Student* loadFromFile(const std::string& filename);
};

#endif // STUDENT_H
