#include "LearningPathSystem.h"
#include "FileManager.h"
#include "ScheduleGenerator.h"
#include "AIEngine.h"
#include "DepthLimitedSearch.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

using namespace std;

LearningPathSystem::LearningPathSystem() : currentStudent(nullptr), nextStudentId(1), nextCourseId(11) {
    FileManager::createDataDirectory();
}

LearningPathSystem::~LearningPathSystem() {
    for (Course* c : allCourses) delete c;
    for (auto& pair : students) delete pair.second;
}

void LearningPathSystem::initializeSampleData() {
    allCourses.push_back(new Course(1, "Intro to Programming", Difficulty::BEGINNER, 4,
        "programming", {}, { "variables", "loops", "functions" }, 5, "Dr. Smith"));
    allCourses.push_back(new Course(2, "Data Structures", Difficulty::INTERMEDIATE, 6,
        "programming", { 1 }, { "arrays", "trees", "graphs" }, 8, "Dr. Johnson"));
    allCourses.push_back(new Course(3, "Algorithms", Difficulty::INTERMEDIATE, 6,
        "programming", { 2 }, { "sorting", "searching", "dp" }, 8, "Dr. Wilson"));
    allCourses.push_back(new Course(4, "Web Development Basics", Difficulty::BEGINNER, 5,
        "web", { 1 }, { "html", "css", "javascript" }, 6, "Prof. Brown"));
    allCourses.push_back(new Course(5, "Frontend Frameworks", Difficulty::INTERMEDIATE, 7,
        "web", { 4 }, { "react", "vue", "state" }, 10, "Prof. Davis"));
    allCourses.push_back(new Course(6, "Backend Development", Difficulty::INTERMEDIATE, 8,
        "web", { 4 }, { "nodejs", "databases", "api" }, 10, "Prof. Miller"));
    allCourses.push_back(new Course(7, "Full Stack Projects", Difficulty::ADVANCED, 10,
        "web", { 5, 6 }, { "deployment", "testing", "devops" }, 15, "Dr. Garcia"));
    allCourses.push_back(new Course(8, "Machine Learning", Difficulty::INTERMEDIATE, 8,
        "ml", { 1, 2 }, { "regression", "classification", "nn" }, 12, "Dr. Martinez"));
    allCourses.push_back(new Course(9, "Deep Learning", Difficulty::ADVANCED, 10,
        "ml", { 8 }, { "cnn", "rnn", "transformers" }, 15, "Dr. Rodriguez"));
    allCourses.push_back(new Course(10, "Database Systems", Difficulty::INTERMEDIATE, 6,
        "programming", { 1 }, { "sql", "nosql", "optimization" }, 7, "Prof. Lee"));

    for (Course* c : allCourses) {
        c->description = "Comprehensive course covering " + c->name;
        c->rating = 4.0 + (rand() % 11) / 10.0;
        c->enrollmentCount = 50 + (rand() % 150);
    }

    setupDataStructures();
    ui.displaySuccess("Sample data initialized with 10 courses");
    
    try {
        FileManager::saveCourses(allCourses);
    } catch (exception& e) {
        ui.displayError(string("Failed to save initial data: ") + e.what());
    }
}

void LearningPathSystem::setupDataStructures() {
    avlTree.clear();
    bst.clear();
    graph.clear();
    
    for (Course* c : allCourses) {
        courseMap[c->id] = c;
        graph.addCourse(c->id);
        bst.insert(c->id, c);

        for (int prereq : c->prerequisites) {
            graph.addPrerequisite(c->id, prereq);
        }
    }

    if (graph.hasCycle()) {
        ui.displayError("Cycle detected in course prerequisites!");
    }
}

void LearningPathSystem::createStudent() {
    ui.displayInfo("Creating new student profile...");

    string name, email, goal;
    int skillLevelInt, hours;

    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter email: ";
    getline(cin, email);
    cout << "Select skill level (0=Novice, 1=Intermediate, 2=Proficient, 3=Expert): ";
    cin >> skillLevelInt;
    cin.ignore();
    cout << "Enter learning goal (programming/web/ml): ";
    getline(cin, goal);
    cout << "Available hours per week: ";
    cin >> hours;
    cin.ignore();

    Student* student = new Student(nextStudentId++, name, email,
        (SkillLevel)skillLevelInt, goal, hours);
    students[student->id] = student;
    currentStudent = student;

    updateAIScores();
    ui.displaySuccess("Student profile created successfully!");
    
    try {
        student->saveToFile("data/student_" + to_string(student->id) + ".txt");
    } catch (exception& e) {
        ui.displayError(string("Failed to save student: ") + e.what());
    }
}

void LearningPathSystem::updateAIScores() {
    if (!currentStudent) return;

    avlTree.clear();
    for (Course* c : allCourses) {
        if (!c->completed) {
            c->aiScore = AIEngine::calculateAIScore(c, currentStudent->skills,
                currentStudent->skillLevel, currentStudent->learningGoal,
                currentStudent->availableHours, currentStudent->completedCourses);
            avlTree.insert(c);
        }
    }
}

void LearningPathSystem::displayRecommendations() {
    if (!currentStudent) {
        ui.displayError("No student profile loaded");
        return;
    }

    vector<Course*> sorted = avlTree.getSortedCourses();
    cout << "\n========== TOP AI RECOMMENDATIONS ==========\n\n";

    int count = 0;
    for (Course* c : sorted) {
        if (count >= 5) break;
        if (graph.canTakeCourse(c->id, currentStudent->completedCourses)) {
            cout << " " << (count + 1) << ". ";
            c->display();
            cout << "\n";
            count++;
        }
    }
    cout << "============================================\n\n";
}

void LearningPathSystem::generateCustomizedPlan() {
    if (!currentStudent) {
        ui.displayError("No student profile loaded");
        return;
    }

    cout << "\n========== GENERATING CUSTOMIZED PLAN ==========\n\n";

    vector<Course*> recommendedCourses;
    vector<Course*> sorted = avlTree.getSortedCourses();

    for (Course* c : sorted) {
        if (recommendedCourses.size() >= 3) break;
        if (graph.canTakeCourse(c->id, currentStudent->completedCourses)) {
            recommendedCourses.push_back(c);
        }
    }

    if (recommendedCourses.empty()) {
        ui.displayInfo("No suitable courses found. Complete prerequisites first.");
        return;
    }

    pathStack.clear();
    DepthLimitedSearch dls(&graph, &courseMap);
    vector<int> tempCompleted = currentStudent->completedCourses;

    for (Course* c : recommendedCourses) {
        vector<int> path = dls.generateLimitedPath(c->id, 4, tempCompleted);
        for (int id : path) {
            pathStack.push(id);
        }
    }

    currentStudent->schedule = ScheduleGenerator::generateSchedule(recommendedCourses, *currentStudent);

    cout << "  [OK] Learning path generated successfully!\n";
    cout << "  [OK] Schedule created with " << recommendedCourses.size() << " courses\n";
    cout << "  [OK] Total weekly commitment: " << currentStudent->schedule.getTotalHours() << " hours\n\n";

    cout << "  Learning Path:\n";
    vector<int> path = pathStack.getPath();
    for (size_t i = 0; i < path.size(); i++) {
        Course* c = courseMap[path[i]];
        cout << "    " << (i + 1) << ". " << c->name << " (" << difficultyToStr(c->difficulty) << ")\n";
    }

    cout << "\n================================================\n\n";
}

void LearningPathSystem::completeCourse() {
    if (!currentStudent) {
        ui.displayError("No student profile loaded");
        return;
    }

    int courseId;
    double score;

    cout << "Enter course ID to complete: ";
    cin >> courseId;
    cout << "Enter your score (0-100): ";
    cin >> score;
    cin.ignore();

    Course* course = bst.search(courseId);
    if (!course) {
        ui.displayError("Course not found!");
        return;
    }

    if (!graph.canTakeCourse(courseId, currentStudent->completedCourses)) {
        ui.displayError("Prerequisites not met!");
        return;
    }

    currentStudent->completeCourse(courseId, course->name, score, course->skills);
    course->completed = true;

    ui.displaySuccess("Course completed: " + course->name);
    cout << "  Score: " << score << "/100\n";
    cout << "  Skills gained: ";
    for (const string& skill : course->skills) {
        cout << skill << " ";
    }
    cout << "\n\n";

    updateAIScores();
}

void LearningPathSystem::runStudentPortal() {
    if (!currentStudent) {
        cout << "\n1. Create New Profile\n2. Load Existing Profile\n3. Back\nChoice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            createStudent();
        } else if (choice == 2) {
            int sid;
            cout << "Enter student ID: ";
            cin >> sid;
            cin.ignore();
            
            if (students.find(sid) != students.end()) {
                currentStudent = students[sid];
                updateAIScores();
            } else {
                ui.displayError("Student not found");
                return;
            }
        } else {
            return;
        }
    }

    while (true) {
        ui.displayStudentMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            currentStudent->displayProfile();
            ui.waitForEnter();
            break;
        case 2:
            displayAllCourses();
            ui.waitForEnter();
            break;
        case 3:
            displayRecommendations();
            ui.waitForEnter();
            break;
        case 4:
            generateCustomizedPlan();
            ui.waitForEnter();
            break;
        case 5:
            currentStudent->schedule.display();
            ui.waitForEnter();
            break;
        case 6:
            completeCourse();
            ui.waitForEnter();
            break;
        case 7: {
            ProgressReport report = currentStudent->generateReport(allCourses.size());
            report.display();
            ui.waitForEnter();
            break;
        }
        case 8: {
            int id;
            cout << "Enter course ID: ";
            cin >> id;
            cin.ignore();
            Course* c = bst.search(id);
            if (c) c->display();
            else ui.displayError("Course not found");
            ui.waitForEnter();
            break;
        }
        case 9:
            currentStudent->completedHistory.display();
            ui.waitForEnter();
            break;
        case 10:
            try {
                currentStudent->saveToFile("data/student_" + to_string(currentStudent->id) + ".txt");
                ui.displaySuccess("Progress saved successfully!");
            } catch (exception& e) {
                ui.displayError(string("Save failed: ") + e.what());
            }
            ui.waitForEnter();
            break;
        case 11:
            currentStudent = nullptr;
            return;
        default:
            ui.displayError("Invalid choice!");
        }
    }
}

void LearningPathSystem::runAdminDashboard() {
    while (true) {
        ui.displayAdminMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            displayAllStudents();
            ui.waitForEnter();
            break;
        case 2:
            displayAllCourses();
            ui.waitForEnter();
            break;
        case 3:
            addNewCourse();
            ui.waitForEnter();
            break;
        case 4:
            removeCourse();
            ui.waitForEnter();
            break;
        case 5:
            displaySystemStatistics();
            ui.waitForEnter();
            break;
        case 6:
            updateCourseInfo();
            ui.waitForEnter();
            break;
        case 7:
            backupAllData();
            ui.waitForEnter();
            break;
        case 8:
            generateReportsForAll();
            ui.waitForEnter();
            break;
        case 9:
            loadAllData();
            ui.waitForEnter();
            break;
        case 10:
            return;
        default:
            ui.displayError("Invalid choice!");
        }
    }
}

void LearningPathSystem::runDoctorInterface() {
    while (true) {
        ui.displayDoctorMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            displayAllStudents();
            ui.waitForEnter();
            break;
        case 2:
            viewStudentProgressReport();
            ui.waitForEnter();
            break;
        case 3:
            performMentalHealthAssessment();
            ui.waitForEnter();
            break;
        case 4:
            addMedicalNote();
            ui.waitForEnter();
            break;
        case 5:
            viewHighStressStudents();
            ui.waitForEnter();
            break;
        case 8:
            reviewStudentSchedule();
            ui.waitForEnter();
            break;
        case 9:
            try {
                FileManager::saveAllStudents(students);
                ui.displaySuccess("Assessment data saved!");
            } catch (exception& e) {
                ui.displayError(string("Save failed: ") + e.what());
            }
            ui.waitForEnter();
            break;
        case 10:
            return;
        default:
            ui.displayError("Invalid choice!");
        }
    }
}

void LearningPathSystem::displayAllCourses() {
    cout << "\n========== ALL COURSES ==========\n\n";
    for (Course* c : allCourses) {
        c->display();
        cout << "\n";
    }
    cout << "=================================\n\n";
}

void LearningPathSystem::displayAllStudents() {
    cout << "\n========== ALL STUDENTS ==========\n\n";
    if (students.empty()) {
        cout << "  No students registered yet.\n";
    }
    else {
        for (auto& pair : students) {
            pair.second->displayProfile();
        }
    }
    cout << "==================================\n\n";
}

void LearningPathSystem::addNewCourse() {
    cout << "\n--- Add New Course ---\n";
    string name, category, instructor, desc;
    int dur, hrs, diffInt;

    cout << "Course Name: ";
    getline(cin, name);
    cout << "Difficulty (0=Beginner, 1=Intermediate, 2=Advanced): ";
    cin >> diffInt;
    cout << "Duration (weeks): ";
    cin >> dur;
    cin.ignore();
    cout << "Category: ";
    getline(cin, category);
    cout << "Hours per week: ";
    cin >> hrs;
    cin.ignore();
    cout << "Instructor: ";
    getline(cin, instructor);
    cout << "Description: ";
    getline(cin, desc);

    Course* newCourse = new Course(nextCourseId++, name, static_cast<Difficulty>(diffInt), dur,
                                    category, {}, {}, hrs, instructor);
    newCourse->description = desc;

    allCourses.push_back(newCourse);
    courseMap[newCourse->id] = newCourse;
    graph.addCourse(newCourse->id);
    bst.insert(newCourse->id, newCourse);

    setupDataStructures();
    ui.displaySuccess("Course added successfully!");
    
    try {
        FileManager::saveCourses(allCourses);
    } catch (exception& e) {
        ui.displayError(string("Failed to save updated courses: ") + e.what());
    }
}

void LearningPathSystem::removeCourse() {
    cout << "\n--- Remove Course ---\n";
    int courseId;
    cout << "Enter Course ID: ";
    cin >> courseId;
    cin.ignore();

    auto it = courseMap.find(courseId);
    if (it != courseMap.end()) {
        Course* course = it->second;
        allCourses.erase(std::remove(allCourses.begin(), allCourses.end(), course), allCourses.end());
        courseMap.erase(it);

        delete course;
        setupDataStructures();
        ui.displaySuccess("Course removed successfully!");

        try {
            FileManager::saveCourses(allCourses);
        } catch (exception& e) {
            ui.displayError(string("Failed to save updated courses: ") + e.what());
        }
    } else {
        ui.displayError("Course not found!");
    }
}

void LearningPathSystem::displaySystemStatistics() {
    cout << "\n========== SYSTEM STATISTICS ==========\n";
    cout << "  Total Courses: " << allCourses.size() << "\n";
    cout << "  Total Students: " << students.size() << "\n";
    cout << "========================================\n";
}

void LearningPathSystem::updateCourseInfo() {
    int courseId;
    cout << "Enter Course ID to update: ";
    cin >> courseId;
    cin.ignore();

    auto it = courseMap.find(courseId);
    if (it == courseMap.end()) {
        ui.displayError("Course not found");
        return;
    }

    Course* c = it->second;
    cout << "Updating Course: " << c->name << "\n";
    cout << "Enter new details (leave blank to keep unchanged):\n";

    string name, instructor, description;
    int dur, hrs, diffInt;

    cout << "Name (" << c->name << "): ";
    getline(cin, name);
    cout << "Instructor (" << c->instructor << "): ";
    getline(cin, instructor);
    cout << "Description: ";
    getline(cin, description);
    cout << "Duration (weeks, " << c->durationWeeks << "): ";
    cin >> dur;
    cout << "Hours/Week (" << c->hoursPerWeek << "): ";
    cin >> hrs;
    cout << "Difficulty (0=Beginner, 1=Intermediate, 2=Advanced): ";
    cin >> diffInt;
    cin.ignore();

    if (!name.empty()) c->name = name;
    if (!instructor.empty()) c->instructor = instructor;
    if (!description.empty()) c->description = description;
    if (dur > 0) c->durationWeeks = dur;
    if (hrs > 0) c->hoursPerWeek = hrs;
    c->difficulty = static_cast<Difficulty>(diffInt);

    setupDataStructures();
    ui.displaySuccess("Course updated successfully!");
}

void LearningPathSystem::backupAllData() {
    try {
        FileManager::saveCourses(allCourses);
        FileManager::saveAllStudents(students);
        ui.displaySuccess("All data backed up successfully!");
    } catch (exception& e) {
        ui.displayError(string("Backup failed: ") + e.what());
    }
}

void LearningPathSystem::generateReportsForAll() {
    cout << "\n--- Generate Reports for All Students ---\n";
    for (const auto& pair : students) {
        ProgressReport report = pair.second->generateReport(allCourses.size());
        report.display();
    }
}

void LearningPathSystem::loadAllData() {
    try {
        allCourses = FileManager::loadCourses();
        students = FileManager::loadAllStudents();
        setupDataStructures();
        ui.displaySuccess("Data loaded successfully!");
    } catch (exception& e) {
        ui.displayError(string("Failed to load data: ") + e.what());
    }
}

void LearningPathSystem::viewStudentProgressReport() {
    int sid;
    cout << "Enter Student ID: ";
    cin >> sid;
    cin.ignore();

    if (students.find(sid) == students.end()) {
        ui.displayError("Student not found!");
        return;
    }

    ProgressReport report = students[sid]->generateReport(allCourses.size());
    report.display();
}

void LearningPathSystem::performMentalHealthAssessment() {
    int sid;
    cout << "Enter Student ID for assessment: ";
    cin >> sid;
    cin.ignore();
    
    auto it = students.find(sid);
    if (it == students.end()) {
        ui.displayError("Student not found!");
        return;
    }
    
    Student* student = it->second;
    cout << "Performing mental health assessment for " << student->name << "...\n";
    cout << "Current stress level: " << student->stressLevel << "/10\n";

    int newStressLevel;
    cout << "Enter new stress level (1-10): ";
    cin >> newStressLevel;
    cin.ignore();
    student->stressLevel = newStressLevel;

    ui.displaySuccess("Assessment updated for " + student->name);
}

void LearningPathSystem::addMedicalNote() {
    int sid;
    cout << "Enter Student ID: ";
    cin >> sid;
    cin.ignore();

    if (students.find(sid) == students.end()) {
        ui.displayError("Student not found!");
        return;
    }

    string note;
    cout << "Enter medical note: ";
    getline(cin, note);

    students[sid]->mentalHealthNote = note;
    ui.displaySuccess("Medical note added!");
}

void LearningPathSystem::viewHighStressStudents() {
    cout << "\n--- Students with High Stress Levels ---\n";
    for (const auto& pair : students) {
        Student* student = pair.second;
        if (student->stressLevel >= 7) {
            cout << student->name << " (" << student->email
                << ") - Stress Level: " << student->stressLevel << "\n";
        }
    }
}

void LearningPathSystem::reviewStudentSchedule() {
    int sid;
    cout << "Enter Student ID: ";
    cin >> sid;
    cin.ignore();

    auto it = students.find(sid);
    if (it == students.end()) {
        ui.displayError("Student not found!");
        return;
    }

    it->second->schedule.display();
}

void LearningPathSystem::run() {
    ui.displayWelcome();
    initializeSampleData();

    while (true) {
        int role = ui.displayRoleSelection();

        switch (role) {
        case 1:
            runStudentPortal();
            break;
        case 2:
            runAdminDashboard();
            break;
        case 3:
            runDoctorInterface();
            break;
        case 4:
            cout << "Exiting system. Goodbye!\n";
            return;
        default:
            ui.displayError("Invalid choice!");
        }
    }
}
