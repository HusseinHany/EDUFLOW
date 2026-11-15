#include "ScheduleGenerator.h"
#include "ScheduleSlot.h"
#include <algorithm>

using namespace std;

// Places each course in 2-hour evening blocks, Monday to Friday, starting at
// 18:00 and moving to a later block once a full week of that block is taken.
// Every (day, start hour) pair is tried at most once, so the loop always ends:
// when the week is full, the remaining hours are simply left unscheduled.
WeeklySchedule ScheduleGenerator::generateSchedule(vector<Course*>& courses, Student& /*student*/) {
    WeeklySchedule schedule;

    const vector<ScheduleDay> weekdays = {
        ScheduleDay::MONDAY, ScheduleDay::TUESDAY, ScheduleDay::WEDNESDAY,
        ScheduleDay::THURSDAY, ScheduleDay::FRIDAY
    };
    const vector<int> startHours = { 18, 20, 16, 14, 8, 10 };
    const int slotLength = 2;

    size_t dayIndex = 0;
    size_t hourIndex = 0;

    for (Course* course : courses) {
        int hoursNeeded = max(0, course->hoursPerWeek);

        while (hoursNeeded > 0 && hourIndex < startHours.size()) {
            int hoursThisSlot = min(hoursNeeded, slotLength);

            ScheduleSlot slot(weekdays[dayIndex], startHours[hourIndex], hoursThisSlot,
                course->id, course->name, "Study");

            if (schedule.addSlot(slot)) {
                hoursNeeded -= hoursThisSlot;
            }

            dayIndex++;
            if (dayIndex >= weekdays.size()) {
                dayIndex = 0;
                hourIndex++;
            }
        }
    }

    return schedule;
}
