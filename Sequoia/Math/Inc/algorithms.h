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
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/* Public Includes */

/* GLEW Includes */

/* Private Includes */
#include "vector3f.h"
#include "vector3i.h"

/* Public Macros */

/* Public Enumerations and Structures */

using namespace vector3f;
using namespace vector3i;

namespace algorithms {

	class Algorithms {

		// Private variables

		public:
		Algorithms();
		~Algorithms();

		/**
		 * @brief This function uses the 3D shoelace algorithm to compute the volume of a 3D mesh. 
		 * 
		 * @param vertecies The list of vertices (x, y, z) that make up the 3D mesh
		 * @param vertexConnectionList List that contain the instructions for making each triangle
		 * out of the list of vertices. Each vector in this list points to 3 vertecies in the vertices
		 * list i.e x -> vertices[x], y -> vertices[y] and z -> vertices[z] and these three vertices
		 * will make up a single triangle
		 * @param numTriangles The number of triangles that make up the 3D mesh. This is also the number
		 * of vectors in the vertexConnectionList
		 * @return float The volume of the 3D mesh
		 */
		static float compute_volume(Vector3f* vertecies, Vector3i* vertexConnectionList, int numTriangles);
	};
} // namespace algorithms

#endif // ALGORITHMS_H
