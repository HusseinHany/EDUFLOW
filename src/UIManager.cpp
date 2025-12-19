#include "UIManager.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void UIManager::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void UIManager::displayWelcome() {
    clearScreen();
    cout << "\n";
    cout << "========================================================\n";
    cout << "                                                        \n";
    cout << "    ** PERSONALIZED AI LEARNING PATH GENERATOR **       \n";
    cout << "                                                        \n";
    cout << "        Smart Scheduling - Progress Tracking           \n";
    cout << "        Multi-Role Interface - AI-Powered              \n";
    cout << "                                                        \n";
    cout << "========================================================\n\n";
}

int UIManager::displayRoleSelection() {
    cout << "\n========== SELECT YOUR ROLE ==========\n";
    cout << "\n  1. Student Portal\n";
    cout << "  2. Admin Dashboard\n";
    cout << "  3. Doctor/Counselor Interface\n";
    cout << "  4. Exit\n\n";
    cout << "--------------------------------------\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

void UIManager::displayStudentMenu() {
    cout << "\n========== STUDENT PORTAL ==========\n";
    cout << "\n  1. View My Profile\n";
    cout << "  2. View Available Courses\n";
    cout << "  3. Get AI Recommendations\n";
    cout << "  4. Generate Learning Path\n";
    cout << "  5. View My Schedule\n";
    cout << "  6. Complete a Course\n";
    cout << "  7. View Progress Report\n";
    cout << "  8. Search Course by ID\n";
    cout << "  9. View Completed History\n";
    cout << "  10. Save My Progress\n";
    cout << "  11. Back to Main Menu\n\n";
    cout << "------------------------------------\n";
    cout << "Enter choice: ";
}

void UIManager::displayAdminMenu() {
    cout << "\n========== ADMIN DASHBOARD ==========\n";
    cout << "\n  1. View All Students\n";
    cout << "  2. Manage Courses\n";
    cout << "  3. Add New Course\n";
    cout << "  4. Remove Course\n";
    cout << "  5. View System Statistics\n";
    cout << "  6. Update Course Info\n";
    cout << "  7. Backup All Data\n";
    cout << "  8. Generate Reports for All\n";
    cout << "  9. Load Data from Files\n";
    cout << "  10. Back to Main Menu\n\n";
    cout << "-------------------------------------\n";
    cout << "Enter choice: ";
}

void UIManager::displayDoctorMenu() {
    cout << "\n========== DOCTOR/COUNSELOR INTERFACE ==========\n";
    cout << "\n  1. View All Students\n";
    cout << "  2. View Student Progress Report\n";
    cout << "  3. Mental Health Assessment\n";
    cout << "  4. Add Medical Note to Report\n";
    cout << "  5. View High Stress Students\n";
    cout << "  6. View Performance Analytics\n";
    cout << "  7. Provide Recommendations\n";
    cout << "  8. Review Student Schedule\n";
    cout << "  9. Save Assessment Data\n";
    cout << "  10. Back to Main Menu\n\n";
    cout << "------------------------------------------------\n";
    cout << "Enter choice: ";
}

void UIManager::displaySuccess(const string& message) {
    cout << "\n[SUCCESS] " << message << "\n\n";
}

void UIManager::displayError(const string& message) {
    cout << "\n[ERROR] " << message << "\n\n";
}

void UIManager::displayInfo(const string& message) {
    cout << "\n[INFO] " << message << "\n\n";
}

void UIManager::waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.get();
}
