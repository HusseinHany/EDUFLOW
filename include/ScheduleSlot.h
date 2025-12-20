#ifndef SCHEDULESLOT_H
#define SCHEDULESLOT_H

#include <string>
#include "Enumerations.h"

// ============ SCHEDULE SLOT CLASS ============
class ScheduleSlot {
public:
    ScheduleDay day;
    int startHour;
    int duration;
    int courseId;
    std::string courseName;
    std::string activity;

    ScheduleSlot(ScheduleDay d, int start, int dur, int cid, std::string cname, std::string act);
    
    void display() const;
    std::string serialize() const;
    static ScheduleSlot deserialize(const std::string& line);
};

#endif // SCHEDULESLOT_H
