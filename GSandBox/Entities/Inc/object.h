/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for object
 * @version 0.1
 * @date Sun Nov 27 20:31:08 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef OBJECT_H
#define OBJECT_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "mesh.h"
#include "entity.h"
#include "strUtils.h"
#include "debugLog.h"
#include "baseShader.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace mesh;
using namespace strUtils;
using namespace baseShader;

namespace object {

	class Object : public entity::Entity {

		// Private variables
		debugLog::DebugLog log;
		strUtils::StrUtils strUtils;

		public:
		Mesh* mesh;
		int loadShaderId;

		Object();
		~Object();
		void load(string objectData);
		void load(string objectData, BaseShader* shader);
		void load_mesh(string filePath, Entity* entity);
	};
} // namespace object

#endif // OBJECT_H
