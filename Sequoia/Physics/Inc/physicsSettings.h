/**
 * @file physicsSettings.h
 * @author Gian BArta-Dougall
 * @brief
 * @version 0.1
 * @date 2023-01-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef PHYSICS_SETTINGS_H
#define PHYSICS_SETTINGS_H

/* C Library Includes */
#include <string>
#include <stdlib.h>

/* GLEW Includes */

/* Personal Includes */
#include "strUtils.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace strUtils;

namespace physicsSettings {

	class PhysicsSettings {

		// Private variables

		public:
		PhysicsSettings();
		~PhysicsSettings();

		void load_values(string line) {
			
			string data[2];
			StrUtils::split_string(line, data, 0, ',');
			
			GRAVITY = stof(data[1]);
		}

		float GRAVITY;
	};
} // namespace physicsSettings

#endif // PHYSICS_SETTINGS_H