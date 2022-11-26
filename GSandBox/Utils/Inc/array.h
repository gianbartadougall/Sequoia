/**
 * @file array.h
 * @author Gian Barta-Dougall
 * @brief System file for array
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
#ifndef ARRAY_H
#define ARRAY_H

/* GLEW Includes */

/* Private Includes */

namespace array {

	class Array {

		// Private variables

		public:
		static void print_farray(float* array, int length);
		static void print_iarray(int* array, int length);
	};
} // namespace array

#endif // ARRAY_H
