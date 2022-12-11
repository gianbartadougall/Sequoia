/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for strUtils
 * @version 0.1
 * @date Sun Dec 11 14:24:24 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef STR_UTILS_H
#define STR_UTILS_H

/* Public Includes */
#include <string>

/* GLEW Includes */

/* Private Includes */

/* Public Macros */

/* Public Enumerations and Structures */

using namespace std;

namespace strUtils {

	class StrUtils {

		// Private variables

		public:
		StrUtils();
		~StrUtils();

		void split_string(string line, string* splitData, int start, char delimiter);
	};
}

#endif // STR_UTILS_H
