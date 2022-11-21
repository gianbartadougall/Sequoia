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

#include <GL/glew.h>

namespace game {

	class Game {

		// Private variables
		void render(float mat[16], GLuint vbo);

		public:
		Game();
		~Game();

		void run();
	};

} // namespace game

#endif // GAMELOOP_H
