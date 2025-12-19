#ifndef LEARNINGPATHSYSTEM_H
#define LEARNINGPATHSYSTEM_H

#include <vector>
#include <map>
#include "Course.h"
#include "Student.h"
#include "AVLTree.h"
#include "BST.h"
#include "Graph.h"
#include "PathStack.h"
#include "UIManager.h"

// ============ MAIN SYSTEM CLASS ============
class LearningPathSystem {
private:
    std::vector<Course*> allCourses;
    std::map<int, Course*> courseMap;
    std::map<int, Student*> students;
    Student* currentStudent;
    AVLTree avlTree;
    BST bst;
    Graph graph;
    PathStack pathStack;
    UIManager ui;
    int nextStudentId;
    int nextCourseId;

public:
    LearningPathSystem();
    ~LearningPathSystem();
    
    void initializeSampleData();
    void setupDataStructures();
    void createStudent();
    void updateAIScores();
    void displayRecommendations();
    void generateCustomizedPlan();
    void completeCourse();
    void runStudentPortal();
    void runAdminDashboard();
    void runDoctorInterface();
    void displayAllCourses();
    void displayAllStudents();
    void addNewCourse();
    void removeCourse();
    void displaySystemStatistics();
    void updateCourseInfo();
    void backupAllData();
    void generateReportsForAll();
    void loadAllData();
    void viewStudentProgressReport();
    void performMentalHealthAssessment();
    void addMedicalNote();
    void viewHighStressStudents();
    void reviewStudentSchedule();
    void run();
};

#endif // LEARNINGPATHSYSTEM_H
