#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "Enumerations.h"

// ============ COURSE CLASS ============
class Course {
public:
    int id;
    std::string name;
    Difficulty difficulty;
    int durationWeeks;
    std::string category;
    std::vector<int> prerequisites;
    std::vector<std::string> skills;
    double aiScore;
    bool completed;
    int hoursPerWeek;
    std::string instructor;
    std::string description;
    double rating;
    int enrollmentCount;

    Course();
    Course(int i, std::string n, Difficulty d, int dur, std::string cat, std::vector<int> prereqs,
        std::vector<std::string> sk, int hrs = 5, std::string inst = "Instructor");
    
    void display() const;
    std::string serialize() const;
    static Course* deserialize(const std::string& line);
};

#endif // COURSE_H
