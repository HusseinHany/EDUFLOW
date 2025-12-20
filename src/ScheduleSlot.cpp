#include "ScheduleSlot.h"
#include "UtilityFunctions.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

ScheduleSlot::ScheduleSlot(ScheduleDay d, int start, int dur, int cid, string cname, string act)
    : day(d), startHour(start), duration(dur), courseId(cid),
    courseName(cname), activity(act) {
}

void ScheduleSlot::display() const {
    cout << "    " << dayToStr(day) << " "
        << setfill('0') << setw(2) << startHour << ":00 - "
        << setw(2) << (startHour + duration) << ":00"
        << " | " << courseName << " (" << activity << ")\n";
}

string ScheduleSlot::serialize() const {
    stringstream ss;
    ss << (int)day << "," << startHour << "," << duration << ","
       << courseId << "," << courseName << "," << activity;
    return ss.str();
}

ScheduleSlot ScheduleSlot::deserialize(const string& line) {
    vector<string> parts = split(line, ',');
    return ScheduleSlot(
        (ScheduleDay)stoi(parts[0]),
        stoi(parts[1]),
        stoi(parts[2]),
        stoi(parts[3]),
        parts[4],
        parts[5]
    );
}
