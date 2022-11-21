/**
 * @file log.cpp
 * @author Gian Barta-Dougall
 * @brief System file for log
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
/* Public Includes */
#include <iostream>
#include <windows.h>

/* Private Includes */
#include "debugLog.h"

/* Private Macros */
#define TEXT_COLOUR_RED	   "[31m"
#define TEXT_COLOUR_BLUE   "[34m"
#define TEXT_COLOUR_YELLOW "[93m"
#define TEXT_COLOUR_WHITE  "[0m"

using namespace std;
using namespace debugLog;

DebugLog::DebugLog() {}

DebugLog::~DebugLog() {}

void DebugLog::log_error(string msg) {
	cout << TEXT_COLOUR_RED << msg << TEXT_COLOUR_WHITE << endl;
}

void DebugLog::log_warning(string msg) {
	cout << TEXT_COLOUR_YELLOW << msg << TEXT_COLOUR_WHITE << endl;
}

void DebugLog::log_message(string msg) {
	cout << TEXT_COLOUR_BLUE << msg << TEXT_COLOUR_WHITE << endl;
}
