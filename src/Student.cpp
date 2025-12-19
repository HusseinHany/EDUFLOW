#include "Student.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

Student::Student() : id(0), skillLevel(SkillLevel::NOVICE), availableHours(10), stressLevel(5) {}

Student::Student(int i, string n, string e, SkillLevel level, string goal, int hours)
    : id(i), name(n), email(e), skillLevel(level), learningGoal(goal),
    availableHours(hours), stressLevel(5) {
}

void Student::completeCourse(int courseId, string courseName, double score, vector<string>& courseSkills) {
    completedCourses.push_back(courseId);
    completedHistory.append(courseId, courseName, score);

    for (const string& skill : courseSkills) {
        if (skills.find(skill) == skills.end()) {
            skills[skill] = 30;
        }
        else {
            skills[skill] = min(100, skills[skill] + 20);
        }
    }

    int count = completedCourses.size();
    if (count >= 3 && skillLevel == SkillLevel::NOVICE) {
        skillLevel = SkillLevel::INTERMEDIATE_LEARNER;
        cout << "Skill level upgraded to: Intermediate!\n";
    }
    else if (count >= 6 && skillLevel == SkillLevel::INTERMEDIATE_LEARNER) {
        skillLevel = SkillLevel::PROFICIENT;
        cout << "Skill level upgraded to: Proficient!\n";
    }
    else if (count >= 10 && skillLevel == SkillLevel::PROFICIENT) {
        skillLevel = SkillLevel::EXPERT;
        cout << "Skill level upgraded to: Expert!\n";
    }
}

void Student::displayProfile() {
    cout << "\n========== STUDENT PROFILE ==========\n";
    cout << "ID: " << id << "\n";
    cout << "Name: " << name << "\n";
    cout << "Email: " << email << "\n";
    cout << "Skill Level: " << skillLevelToStr(skillLevel) << "\n";
    cout << "Learning Goal: " << learningGoal << "\n";
    cout << "Available Time: " << availableHours << " hours/week\n";
    cout << "Completed Courses: " << completedCourses.size() << "\n";
    cout << "Stress Level: " << stressLevel << "/10\n";

    if (!skills.empty()) {
        cout << "\nSkills:\n";
        for (const auto& pair : skills) {
            cout << "  - " << pair.first << ": " << pair.second << "%\n";
        }
    }
    cout << "====================================\n\n";
}

ProgressReport Student::generateReport(int totalCourses) {
    ProgressReport report;
    report.studentName = name;
    report.completedCourses = completedCourses.size();
    report.totalCourses = totalCourses;
    report.averageScore = completedHistory.getAverageScore();
    report.totalStudyHours = schedule.getTotalHours() * 4;
    report.stressLevel = stressLevel;
    report.mentalHealthNote = mentalHealthNote;

    for (const auto& pair : skills) {
        report.completedSkills.push_back(pair.first + " (" + to_string(pair.second) + "%)");
    }

    if (stressLevel >= 7) {
        report.recommendations.push_back("Consider reducing course load");
        report.recommendations.push_back("Schedule breaks between study sessions");
    }
    if (completedHistory.getAverageScore() < 70) {
        report.recommendations.push_back("Review fundamental concepts");
        report.recommendations.push_back("Seek tutoring or study groups");
    }
    if (schedule.getTotalHours() > availableHours) {
        report.recommendations.push_back("Adjust schedule to match available time");
    }

    return report;
}

void Student::saveToFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    file << id << "\n" << name << "\n" << email << "\n"
         << skillLevelToStr(skillLevel) << "\n" << learningGoal << "\n"
         << availableHours << "\n" << stressLevel << "\n";

    file << completedCourses.size() << "\n";
    for (int cid : completedCourses) {
        file << cid << " ";
    }
    file << "\n";

    file << skills.size() << "\n";
    for (const auto& pair : skills) {
        file << pair.first << "," << pair.second << "\n";
    }

    file << mentalHealthNote << "\n";
    
    file << completedHistory.serialize();
    file << schedule.serialize();

    file.close();
}

Student* Student::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open file: " + filename);
    }

    Student* s = new Student();
    string line;

    file >> s->id;
    file.ignore();
    getline(file, s->name);
    getline(file, s->email);
    getline(file, line);
    s->skillLevel = strToSkillLevel(line);
    getline(file, s->learningGoal);
    file >> s->availableHours >> s->stressLevel;
    file.ignore();

    int completedCount;
    file >> completedCount;
    s->completedCourses.resize(completedCount);
    for (int i = 0; i < completedCount; i++) {
        file >> s->completedCourses[i];
    }
    file.ignore();

    int skillCount;
    file >> skillCount;
    file.ignore();
    for (int i = 0; i < skillCount; i++) {
        getline(file, line);
        vector<string> parts = split(line, ',');
        if (parts.size() == 2) {
            s->skills[parts[0]] = stoi(parts[1]);
        }
    }

    getline(file, s->mentalHealthNote);
    
    s->completedHistory.deserialize(file);
    s->schedule.deserialize(file);

    file.close();
    return s;
}
