#ifndef AIENGINE_H
#define AIENGINE_H

#include <map>
#include <string>
#include <vector>
#include "Course.h"
#include "Enumerations.h"

// ============ AI ENGINE CLASS ============
class AIEngine {
public:
    static double calculateAIScore(Course* course, const std::map<std::string, int>& studentSkills,
        SkillLevel skillLevel, std::string learningGoal,
        int availableHours, std::vector<int>& completedCourses);
};

#endif // AIENGINE_H
