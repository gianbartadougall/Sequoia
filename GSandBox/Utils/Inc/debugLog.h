/**
 * @file log.h
 * @author Gian Barta-Dougall
 * @brief System file for log
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
#ifndef LOG_H
#define LOG_H

/* GLEW Includes */

/* Private Includes */
#include <string>

using namespace std;

namespace debugLog {

	class DebugLog {

		// Private variables

		public:
		DebugLog();
		~DebugLog();

		static void log_error(string msg);
		static void log_warning(string msg);
		static void log_message(string msg);
	};

} // namespace debugLog

#endif // LOG_H
