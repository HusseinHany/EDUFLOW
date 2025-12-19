#ifndef WEEKLYSCHEDULE_H
#define WEEKLYSCHEDULE_H

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "ScheduleSlot.h"
#include "Enumerations.h"

// ============ WEEKLY SCHEDULE CLASS ============
class WeeklySchedule {
private:
    std::vector<ScheduleSlot> slots;
    std::map<ScheduleDay, int> dailyHours;
    int totalHoursPerWeek;

public:
    WeeklySchedule();
    
    bool addSlot(const ScheduleSlot& slot);
    void display() const;
    int getTotalHours() const;
    std::vector<ScheduleSlot> getSlots() const;
    void clear();
    std::string serialize() const;
    void deserialize(std::ifstream& file);
};

#endif // WEEKLYSCHEDULE_H
