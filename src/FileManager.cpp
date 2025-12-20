#include "FileManager.h"
#include "UtilityFunctions.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

void FileManager::saveCourses(const vector<Course*>& courses, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot create courses file");
    }

    file << courses.size() << "\n";
    for (const Course* c : courses) {
        file << c->serialize() << "\n";
    }
    file.close();
    cout << "Courses saved successfully to " << filename << "\n";
}

vector<Course*> FileManager::loadCourses(const string& filename) {
    vector<Course*> courses;
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot open courses file");
    }

    int count;
    file >> count;
    file.ignore();

    for (int i = 0; i < count; i++) {
        string line;
        getline(file, line);
        if (!line.empty()) {
            Course* c = Course::deserialize(line);
            if (c) courses.push_back(c);
        }
    }

    file.close();
    cout << "Loaded " << courses.size() << " courses from " << filename << "\n";
    return courses;
}

void FileManager::saveAllStudents(const map<int, Student*>& students) {
    ofstream indexFile("data/students_index.txt");
    if (!indexFile.is_open()) {
        throw runtime_error("Cannot create students index file");
    }

    indexFile << students.size() << "\n";
    for (const auto& pair : students) {
        string filename = "data/student_" + to_string(pair.first) + ".txt";
        indexFile << pair.first << "," << filename << "\n";
        pair.second->saveToFile(filename);
    }
    indexFile.close();
    cout << "Saved " << students.size() << " student profiles\n";
}

map<int, Student*> FileManager::loadAllStudents() {
    map<int, Student*> students;
    ifstream indexFile("data/students_index.txt");
    if (!indexFile.is_open()) {
        throw runtime_error("Cannot open students index file");
    }

    int count;
    indexFile >> count;
    indexFile.ignore();

    for (int i = 0; i < count; i++) {
        string line;
        getline(indexFile, line);
        vector<string> parts = split(line, ',');
        if (parts.size() == 2) {
            int id = stoi(parts[0]);
            try {
                Student* s = Student::loadFromFile(parts[1]);
                students[id] = s;
            } catch (exception& e) {
                cerr << "Error loading student " << id << ": " << e.what() << "\n";
            }
        }
    }

    indexFile.close();
    cout << "Loaded " << students.size() << " student profiles\n";
    return students;
}

void FileManager::createDataDirectory() {
    #ifdef _WIN32
        system("if not exist data mkdir data");
    #else
        system("mkdir -p data");
    #endif
}
