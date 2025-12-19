#include "AIEngine.h"
#include <algorithm>

using namespace std;

double AIEngine::calculateAIScore(Course* course, const map<string, int>& studentSkills,
    SkillLevel skillLevel, string learningGoal,
    int availableHours, vector<int>& completedCourses) {
    double score = 0.0;

    // Goal alignment (35%)
    if (course->category == learningGoal) score += 35.0;
    else if (course->category.find(learningGoal) != string::npos) score += 20.0;

    // Difficulty match (30%)
    switch (skillLevel) {
    case SkillLevel::NOVICE:
        if (course->difficulty == Difficulty::BEGINNER) score += 30.0;
        else if (course->difficulty == Difficulty::INTERMEDIATE) score += 10.0;
        break;
    case SkillLevel::INTERMEDIATE_LEARNER:
        if (course->difficulty == Difficulty::BEGINNER) score += 15.0;
        else if (course->difficulty == Difficulty::INTERMEDIATE) score += 30.0;
        else if (course->difficulty == Difficulty::ADVANCED) score += 10.0;
        break;
    case SkillLevel::PROFICIENT:
        if (course->difficulty == Difficulty::INTERMEDIATE) score += 20.0;
        else if (course->difficulty == Difficulty::ADVANCED) score += 30.0;
        break;
    case SkillLevel::EXPERT:
        if (course->difficulty == Difficulty::ADVANCED) score += 30.0;
        else score += 15.0;
        break;
    }

    // Time feasibility (20%)
    if (course->hoursPerWeek <= availableHours) score += 20.0;
    else if (course->hoursPerWeek <= availableHours * 1.5) score += 10.0;

    // Prerequisites completion (15%)
    bool allPrereqsComplete = true;
    for (int prereq : course->prerequisites) {
        if (find(completedCourses.begin(), completedCourses.end(), prereq) == completedCourses.end()) {
            allPrereqsComplete = false;
            break;
        }
    }
    if (allPrereqsComplete) score += 15.0;

    return score;
}
