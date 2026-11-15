#ifndef UTILITYFUNCTIONS_H
#define UTILITYFUNCTIONS_H

#include <string>
#include <vector>
#include "Enumerations.h"

// ============ UTILITY FUNCTIONS ============
std::string difficultyToStr(Difficulty d);
Difficulty strToDifficulty(const std::string& s);
std::string skillLevelToStr(SkillLevel s);
SkillLevel strToSkillLevel(const std::string& s);
std::string dayToStr(ScheduleDay d);
ScheduleDay strToDay(const std::string& s);
std::vector<std::string> split(const std::string& str, char delimiter);
std::string trim(const std::string& str);

// Reads one line from standard input and parses it as a number.
// Returns `fallback` when the line is empty or not a number, so a menu loop
// sees an invalid choice instead of spinning forever on a failed stream.
// Exits cleanly if standard input is closed.
int readInt(int fallback = -1);
double readDouble(double fallback = -1.0);

// Keeps a value inside [lo, hi].
int clampInt(int value, int lo, int hi);

#endif // UTILITYFUNCTIONS_H
