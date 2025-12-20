#ifndef SCHEDULEGENERATOR_H
#define SCHEDULEGENERATOR_H

#include <vector>
#include "WeeklySchedule.h"
#include "Course.h"
#include "Student.h"

// Forward declaration to avoid circular dependency
class Student;

// ============ SCHEDULE GENERATOR CLASS ============
class ScheduleGenerator {
public:
    static WeeklySchedule generateSchedule(std::vector<Course*>& courses, Student& student);
};

#endif // SCHEDULEGENERATOR_H
