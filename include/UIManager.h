#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>

// ============ UI MANAGER CLASS ============
class UIManager {
private:
    void clearScreen();

public:
    void displayWelcome();
    int displayRoleSelection();
    void displayStudentMenu();
    void displayAdminMenu();
    void displayDoctorMenu();
    void displaySuccess(const std::string& message);
    void displayError(const std::string& message);
    void displayInfo(const std::string& message);
    void waitForEnter();
};

#endif // UIMANAGER_H
