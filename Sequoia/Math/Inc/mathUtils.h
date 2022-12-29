/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for math constants
 * @version 0.1
 * @date Wed Dec 28 20:59:16 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef MATH_UTILS_H
#define MATH_UTILS_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */

/* Public Macros */

namespace mathUtils {

#define PI		  3.141592654
#define PI_MULT_2 (PI * 2)
#define PI_DIV_2  (PI / 2)

#define DEG_TO_RAD(deg) (deg * (PI / 180))
#define RAD_TO_DEG(rad) (rad * (180 / PI))

} // namespace mathUtils

#endif // MATH_UTILS_H
