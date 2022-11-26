/* Public Includes */
/**
 * @file arrays.cpp
 * @author Gian Barta-Dougall
 * @brief System file for arrays
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
/* Public Includes */
#include <iostream>

/* Private Includes */
#include "array.h"

/* Private Macros */

using namespace array;

void Array::print_farray(float* array, int length) {

	for (int i = 0; i < length; i++) {

		std::cout << array[i] << " ";
		// std::cout << "i[" << i << "]: " << array[i] << " ";

		if ((i + 1) % 3 == 0) {
			std::cout << "\n";
		}
	}
}

void Array::print_iarray(int* array, int length) {

	for (int i = 0; i < length; i++) {

		std::cout << array[i] << " ";
		// std::cout << "i[" << i << "]: " << array[i] << " ";

		if ((i + 1) % 3 == 0) {
			std::cout << "\n";
		}
	}
}