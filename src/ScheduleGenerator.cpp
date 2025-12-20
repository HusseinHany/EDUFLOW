#include "ScheduleGenerator.h"
#include "ScheduleSlot.h"
#include <algorithm>

using namespace std;

WeeklySchedule ScheduleGenerator::generateSchedule(vector<Course*>& courses, Student& student) {
    WeeklySchedule schedule;

    int hoursPerDay = max(1, student.availableHours / 5);
    vector<ScheduleDay> weekdays = {
        ScheduleDay::MONDAY, ScheduleDay::TUESDAY, ScheduleDay::WEDNESDAY,
        ScheduleDay::THURSDAY, ScheduleDay::FRIDAY
    };

    int dayIndex = 0;
    int startHour = 18;

    for (Course* course : courses) {
        int hoursNeeded = course->hoursPerWeek;

        while (hoursNeeded > 0 && dayIndex < weekdays.size()) {
            int hoursThisSlot = min(hoursNeeded, 2);

            ScheduleSlot slot(weekdays[dayIndex], startHour, hoursThisSlot,
                course->id, course->name, "Study");

            if (schedule.addSlot(slot)) {
                hoursNeeded -= hoursThisSlot;
            }

            dayIndex++;
            if (dayIndex >= weekdays.size()) {
                dayIndex = 0;
                startHour = (startHour + 2) % 24;
                if (startHour < 8) startHour = 18;
            }
        }
    }

    return schedule;
}
