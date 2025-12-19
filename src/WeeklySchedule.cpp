#include "WeeklySchedule.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <sstream>

using namespace std;

WeeklySchedule::WeeklySchedule() : totalHoursPerWeek(0) {
    for (int i = 0; i < 7; i++) {
        dailyHours[(ScheduleDay)i] = 0;
    }
}

bool WeeklySchedule::addSlot(const ScheduleSlot& slot) {
    for (const auto& existing : slots) {
        if (existing.day == slot.day) {
            int existingEnd = existing.startHour + existing.duration;
            int newEnd = slot.startHour + slot.duration;

            if ((slot.startHour >= existing.startHour && slot.startHour < existingEnd) ||
                (newEnd > existing.startHour && newEnd <= existingEnd) ||
                (slot.startHour <= existing.startHour && newEnd >= existingEnd)) {
                return false;
            }
        }
    }

    slots.push_back(slot);
    dailyHours[slot.day] += slot.duration;
    totalHoursPerWeek += slot.duration;
    return true;
}

void WeeklySchedule::display() const {
    cout << "\n========== WEEKLY SCHEDULE ==========\n";
    cout << "Total Hours: " << totalHoursPerWeek << " hours/week\n\n";

    for (int i = 0; i < 7; i++) {
        ScheduleDay day = (ScheduleDay)i;
        cout << "  " << dayToStr(day) << " (" << dailyHours.at(day) << " hours):\n";

        bool hasSlots = false;
        for (const auto& slot : slots) {
            if (slot.day == day) {
                slot.display();
                hasSlots = true;
            }
        }
        if (!hasSlots) {
            cout << "    No classes scheduled\n";
        }
        cout << "\n";
    }
    cout << "====================================\n\n";
}

int WeeklySchedule::getTotalHours() const { return totalHoursPerWeek; }

vector<ScheduleSlot> WeeklySchedule::getSlots() const { return slots; }

void WeeklySchedule::clear() { 
    slots.clear(); 
    totalHoursPerWeek = 0;
    for (int i = 0; i < 7; i++) {
        dailyHours[(ScheduleDay)i] = 0;
    }
}

string WeeklySchedule::serialize() const {
    stringstream ss;
    ss << slots.size() << "\n";
    for (const auto& slot : slots) {
        ss << slot.serialize() << "\n";
    }
    return ss.str();
}

void WeeklySchedule::deserialize(ifstream& file) {
    clear();
    int count;
    file >> count;
    file.ignore();
    
    for (int i = 0; i < count; i++) {
        string line;
        getline(file, line);
        if (!line.empty()) {
            ScheduleSlot slot = ScheduleSlot::deserialize(line);
            addSlot(slot);
        }
    }
}
