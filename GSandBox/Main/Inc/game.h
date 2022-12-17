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

#define GLEW_STATIC
#include <GL/glew.h>

#include "debugLog.h"
#include "object.h"
#include "entity.h"
#include "vector3f.h"
#include "baseShader.h"
#include "renderer.h"

using namespace object;
using namespace renderer;

namespace game {

	class Game {

		// Private variables
		Object* objects;
		BaseShader* baseShaders;
		GLuint* vaos;

		int* objectListSizes;

		int numEntities = 0;
		int numShaders	= 0;
		int numVaos		= 0;

		Renderer renderer;
		Camera camera;

		void render();

		debugLog::DebugLog log;

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
