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

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "strUtils.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace strUtils;

StrUtils::StrUtils() {}

StrUtils::~StrUtils() {}

/**
 * @brief Splits a line containing three pieces of data all seperated by a common delimiter.
 * E.g
 * 		string line = "data = 0 2 4"
 * 		string results[3];
 *
 * 		// Because the delimiter is a space and there are other spaces in the input string,
 * 		// the start index specifies what index the function will start splitting up data
 * 		split_triplet(line, results, 6, ' ');
 *
 * This code will output
 * 		results[0] = "0"
 * 		results[1] = "2"
 * 		results[2] = "4"
 *
 * @param line The string containing the triplet of data to be split
 * @param splitList An empty list of type string with a length of 3. The split data will be
 * saved into this list
 * @param start The index this function will start searching for delimiters
 * @param delimiter The char the function will split the data on
 */
void StrUtils::split_string(string line, string* splitData, int start, char delimiter) {
	int index = 0;
	for (int i = start; true; i++) {

		if (line[i] == delimiter) {
			splitData[index++] = line.substr(start, i - start);
			start			   = i + 1;
		}

		if (line[i] == '\0') {
			splitData[index++] = line.substr(start, i - start);
			break;
		}
	}
}
