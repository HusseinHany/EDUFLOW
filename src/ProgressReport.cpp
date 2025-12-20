#include "ProgressReport.h"
#include <iostream>
#include <iomanip>

using namespace std;

ProgressReport::ProgressReport() : completedCourses(0), totalCourses(0), averageScore(0.0),
    totalStudyHours(0), stressLevel(5) {
}

void ProgressReport::display() const {
    cout << "\n========== PROGRESS REPORT ==========\n";
    cout << "Student: " << studentName << "\n";
    cout << "Completion: " << completedCourses << "/" << totalCourses
        << " (" << fixed << setprecision(1)
        << (totalCourses > 0 ? (completedCourses * 100.0 / totalCourses) : 0.0) << "%)\n";
    cout << "Average Score: " << averageScore << "/100\n";
    cout << "Total Study Hours: " << totalStudyHours << " hours\n";
    cout << "Stress Level: " << stressLevel << "/10\n";

    if (!completedSkills.empty()) {
        cout << "\nAcquired Skills:\n";
        for (const auto& skill : completedSkills) {
            cout << "  * " << skill << "\n";
        }
    }

    if (!recommendations.empty()) {
        cout << "\nRecommendations:\n";
        for (const auto& rec : recommendations) {
            cout << "  - " << rec << "\n";
        }
    }

    if (!mentalHealthNote.empty()) {
        cout << "\nDoctor's Note: " << mentalHealthNote << "\n";
    }
    cout << "====================================\n\n";
}
