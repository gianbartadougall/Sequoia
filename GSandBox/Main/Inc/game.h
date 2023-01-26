/**
 * @file game.h
 * @author Gian Barta-Dougall
 * @brief System file for game
 * @version 0.1
 * @date --
 *
 * @copyright Copyright (c)
 *
 */
#ifndef GAMELOOP_H
#define GAMELOOP_H

/* C Library Includes */

/* GLEW Includes */
#define GLEW_STATIC
#include <GL/glew.h>

/* Personal Includes */
#include "debugLog.h"
#include "object.h"
#include "entity.h"
#include "vector3f.h"
#include "baseShader.h"
#include "renderer.h"
#include "shaderLoader.h"
#include "physicsSettings.h"
#include "objectLoader.h"

using namespace object;
using namespace renderer;
using namespace shaderLoader;
using namespace physicsSettings;
using namespace objectLoader;

namespace game {

	class Game {

		// Private variables
		ObjectLoader objectLoader;
		Object* objects;
		BaseShader* baseShaders;

		int* objectListSizes;

		int numEntities = 0;
		int numShaders	= 0;
		int numVaos		= 0;
		int numVbos		= 0;

		PhysicsSettings phys;
		Renderer renderer;
		Camera camera;
		ShaderLoader shaderLoader;

		public:
		Game();
		~Game();

		void run();
		void load_game(string filePath);
		void render(Object* objects);
		void detect_keys();
		void detect_mouse();
	};

} // namespace game

#endif // GAMELOOP_H
