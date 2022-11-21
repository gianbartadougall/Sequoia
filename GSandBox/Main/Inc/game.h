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

namespace game {

	class Game {

		// Private variables

		void render();

		public:

		Game();
		~Game();

		void run();

	};
}

#endif // GAMELOOP_H
