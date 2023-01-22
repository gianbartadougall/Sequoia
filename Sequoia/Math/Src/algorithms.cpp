/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for algorithms
 * @version 0.1
 * @date Sat Jan 07 20:07:07 2023

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "algorithms.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace algorithms;

Algorithms::Algorithms() {}

Algorithms::~Algorithms() {}

float Algorithms::compute_volume(Vector3f* vertecies, Vector3i* vertexConnectionList, int numTriangles) {

	// Sum the determinate of each triangle. Divide by 6 to get volume
	float volume = 0;
	for (int i = 0; i < numTriangles; i++) {

		// Create list of vertices
		Vector3f v1 = vertecies[vertexConnectionList[i].v[0]];
		Vector3f v2 = vertecies[vertexConnectionList[i].v[1]];
		Vector3f v3 = vertecies[vertexConnectionList[i].v[2]];

		// Compute the determinant of a matrix consisting of the above 3 vectors
		volume += (v1.v[0] * v2.v[1] * v3.v[2]) + (v1.v[2] * v2.v[0] * v3.v[1]) + (v1.v[1] * v2.v[2] * v3.v[0]) -
				  (v1.v[2] * v2.v[1] * v3.v[0]) - (v1.v[1] * v2.v[0] * v3.v[2]) - (v1.v[0] * v2.v[2] * v3.v[1]);
	}

	return volume / 6;
}
