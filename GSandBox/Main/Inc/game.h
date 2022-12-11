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

using namespace object;

namespace game {

	class Game {

		// Private variables
		Object* objects;
		GLuint vao;

		void render();

		debugLog::DebugLog log;

		public:
		Game();
		~Game();

		void run();
		void load_game(string filePath);
		void render(Object* objects, int numObjects);
	};

} // namespace game

#endif // GAMELOOP_H
