#include "UtilityFunctions.h"
#include <sstream>

using namespace std;

string difficultyToStr(Difficulty d) {
    switch (d) {
    case Difficulty::BEGINNER: return "Beginner";
    case Difficulty::INTERMEDIATE: return "Intermediate";
    case Difficulty::ADVANCED: return "Advanced";
    }
    return "";
}

Difficulty strToDifficulty(const string& s) {
    if (s == "Beginner") return Difficulty::BEGINNER;
    if (s == "Intermediate") return Difficulty::INTERMEDIATE;
    if (s == "Advanced") return Difficulty::ADVANCED;
    return Difficulty::BEGINNER;
}

string skillLevelToStr(SkillLevel s) {
    switch (s) {
    case SkillLevel::NOVICE: return "Novice";
    case SkillLevel::INTERMEDIATE_LEARNER: return "Intermediate";
    case SkillLevel::PROFICIENT: return "Proficient";
    case SkillLevel::EXPERT: return "Expert";
    }
    return "";
}

SkillLevel strToSkillLevel(const string& s) {
    if (s == "Novice") return SkillLevel::NOVICE;
    if (s == "Intermediate") return SkillLevel::INTERMEDIATE_LEARNER;
    if (s == "Proficient") return SkillLevel::PROFICIENT;
    if (s == "Expert") return SkillLevel::EXPERT;
    return SkillLevel::NOVICE;
}

string dayToStr(ScheduleDay d) {
    switch (d) {
    case ScheduleDay::MONDAY: return "Monday";
    case ScheduleDay::TUESDAY: return "Tuesday";
    case ScheduleDay::WEDNESDAY: return "Wednesday";
    case ScheduleDay::THURSDAY: return "Thursday";
    case ScheduleDay::FRIDAY: return "Friday";
    case ScheduleDay::SATURDAY: return "Saturday";
    case ScheduleDay::SUNDAY: return "Sunday";
    }
    return "";
}

ScheduleDay strToDay(const string& s) {
    if (s == "Monday") return ScheduleDay::MONDAY;
    if (s == "Tuesday") return ScheduleDay::TUESDAY;
    if (s == "Wednesday") return ScheduleDay::WEDNESDAY;
    if (s == "Thursday") return ScheduleDay::THURSDAY;
    if (s == "Friday") return ScheduleDay::FRIDAY;
    if (s == "Saturday") return ScheduleDay::SATURDAY;
    if (s == "Sunday") return ScheduleDay::SUNDAY;
    return ScheduleDay::MONDAY;
}

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        if (!token.empty()) tokens.push_back(token);
    }
    return tokens;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}
