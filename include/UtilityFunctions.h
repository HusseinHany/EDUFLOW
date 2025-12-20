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

#endif // UTILITYFUNCTIONS_H
