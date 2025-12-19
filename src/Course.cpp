#include "Course.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

Course::Course() : id(0), difficulty(Difficulty::BEGINNER), durationWeeks(0),
    aiScore(0.0), completed(false), hoursPerWeek(5), rating(0.0), enrollmentCount(0) {
}

Course::Course(int i, string n, Difficulty d, int dur, string cat, vector<int> prereqs,
    vector<string> sk, int hrs, string inst)
    : id(i), name(n), difficulty(d), durationWeeks(dur), category(cat),
    prerequisites(prereqs), skills(sk), aiScore(0.0), completed(false),
    hoursPerWeek(hrs), instructor(inst), rating(0.0), enrollmentCount(0) {
}

void Course::display() const {
    cout << "  [" << id << "] " << name << " (" << difficultyToStr(difficulty) << ")\n";
    cout << "      Category: " << category << " | Duration: " << durationWeeks << " weeks\n";
    cout << "      Hours/Week: " << hoursPerWeek << " | Instructor: " << instructor << "\n";
    cout << "      AI Score: " << fixed << setprecision(2) << aiScore;
    cout << " | Rating: " << rating << "/5.0 | Enrolled: " << enrollmentCount << "\n";
    if (!description.empty()) {
        cout << "      Description: " << description << "\n";
    }
}

string Course::serialize() const {
    stringstream ss;
    ss << id << "|" << name << "|" << (int)difficulty << "|" << durationWeeks << "|"
       << category << "|";
    
    for (size_t i = 0; i < prerequisites.size(); i++) {
        ss << prerequisites[i];
        if (i < prerequisites.size() - 1) ss << ",";
    }
    ss << "|";
    
    for (size_t i = 0; i < skills.size(); i++) {
        ss << skills[i];
        if (i < skills.size() - 1) ss << ",";
    }
    ss << "|" << hoursPerWeek << "|" << instructor << "|" << aiScore << "|"
       << completed << "|" << description << "|" << rating << "|" << enrollmentCount;
    
    return ss.str();
}

Course* Course::deserialize(const string& line) {
    vector<string> parts = split(line, '|');
    if (parts.size() < 13) return nullptr;

    Course* c = new Course();
    c->id = stoi(parts[0]);
    c->name = parts[1];
    c->difficulty = (Difficulty)stoi(parts[2]);
    c->durationWeeks = stoi(parts[3]);
    c->category = parts[4];
    
    if (!parts[5].empty()) {
        vector<string> prereqs = split(parts[5], ',');
        for (const string& p : prereqs) {
            c->prerequisites.push_back(stoi(p));
        }
    }
    
    if (!parts[6].empty()) {
        c->skills = split(parts[6], ',');
    }
    
    c->hoursPerWeek = stoi(parts[7]);
    c->instructor = parts[8];
    c->aiScore = stod(parts[9]);
    c->completed = stoi(parts[10]);
    c->description = parts[11];
    c->rating = stod(parts[12]);
    c->enrollmentCount = stoi(parts[13]);
    
    return c;
}
