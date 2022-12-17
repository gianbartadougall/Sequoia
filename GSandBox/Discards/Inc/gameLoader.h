/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for gameLoader
 * @version 0.1
 * @date Sat Dec 17 20:32:36 2022

 *
 * @copyright Copyright (c)
 *
 */
#ifndef GAME_LOADER_H
#define GAME_LOADER_H

/* Public Includes */
#include <string>

/* GLEW Includes */

/* Private Includes */
#include "debugLog.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace std;
using namespace debugLog;

namespace gameLoader {

	class GameLoader {

		/* Private Variables */
		DebugLog log;
		uint8_t search_game_parameters(string filePath);

		public:
		GameLoader();
		~GameLoader();

		int numVaos	   = 0;
		int numShaders = 0;
		int numObjects = 0;

		void load_game(string filePath);
	};
} // namespace gameLoader

#endif // GAME_LOADER_H
