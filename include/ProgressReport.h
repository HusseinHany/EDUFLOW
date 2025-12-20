#ifndef PROGRESSREPORT_H
#define PROGRESSREPORT_H

#include <string>
#include <vector>

// ============ PROGRESS REPORT CLASS ============
class ProgressReport {
public:
    std::string studentName;
    int completedCourses;
    int totalCourses;
    double averageScore;
    int totalStudyHours;
    std::vector<std::string> completedSkills;
    std::vector<std::string> recommendations;
    std::string mentalHealthNote;
    int stressLevel;

    ProgressReport();
    void display() const;
};

#endif // PROGRESSREPORT_H
