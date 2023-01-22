/**
 * @file game.cpp
 * @author Gian Barta-Dougall
 * @brief System file for renderer
 * @version 0.1
 * @date Sat Dec 17 11:23:10 2022

 *
 * @copyright Copyright (c)
 *
 */

/* Public Includes */
#include <iostream>

/* GLEW Includes */

/* Private Includes */
#include "renderer.h"

/* Private Macros */

/* Private Enumerations and Structures */

using namespace renderer;
using namespace std;

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::load_generic_shader_values(Entity* entity) {

	// Create the transformation matrix and load it in the vertex shader
	Matrix4f transformationMatrix;
	transformationMatrix.scale(entity->scale);
	transformationMatrix.rotate(entity->rotation);
	transformationMatrix.translate(entity->position);
	glUniformMatrix4fv(entity->shader->transformationMatrixLocation, 1, GL_FALSE, transformationMatrix.m);
}

void Renderer::load_object_shader_values(Object* object) {

	/* Load Generic Shader Values */
	load_generic_shader_values(object);

	/* Load object specific shader values */
}

void Renderer::render_objects(GLuint* vaos, int numVaos, Object* objects, int* objectListSizes, Camera* camera) {

	/* Updating the view matrix so it is done at least once. This is incase all
		objects that need to be rendered share the same shader. It is important
		that the translation occurs before the rotation because the camera is
		setup such that the camera is always located at the origin and rotating
		the camera is just rotating the entire world so it looks like the camera
		rotated. For the objects to rotate around the camera, you need to displace
		them by the cameras position first before rotating otherwise if you rotate
		first then translate they will rotate about the origin instead of about the
		cameras position */
	// matrix4f::Matrix4f vMat;
	// vMat.translate(camera->position);
	// vMat.rotate(camera->rotation);

	// Loop through every vao and render the all the objects associated with
	// that vao
	int offset = 0;
	for (int vi = 0; vi < numVaos; vi++) {

		// Binding and enabling the vao so that OpenGL uses that vao when
		// the function to draw the objects are called
		glBindVertexArray(vaos[vi]);

		glUniform3f(objects[offset].shader->cameraRotationLocation, camera->rotation.v[0], camera->rotation.v[1],
					camera->rotation.v[2]);
		glUniform3f(objects[offset].shader->cameraPositionLocation, camera->position.v[0], camera->position.v[1],
					camera->position.v[2]);
		// glUniformMatrix4fv(objects[offset].shader->viewMatrixLocation, 1, GL_FALSE, vMat.m);

		// Draw every object that is associated to the currently bound vao
		for (int j = 0; j < objectListSizes[vi]; j++) {

			int k = offset + j;

			// Load the view matrix if required
			if (objects[k].shader->programId != this->currentShaderId) {
				this->currentShaderId = objects[k].shader->programId;

				// Load the new shader
				glUseProgram(this->currentShaderId);

				glUniform3f(objects[k].shader->cameraRotationLocation, camera->rotation.v[0], camera->rotation.v[1],
							camera->rotation.v[2]);
				glUniform3f(objects[k].shader->cameraPositionLocation, camera->position.v[0], camera->position.v[1],
							camera->position.v[2]);
				// vMat.set_to_identity();
				// vMat.translate(camera->position);
				// vMat.rotate(camera->rotation);
				// glUniformMatrix4fv(objects[k].shader->viewMatrixLocation, 1, GL_FALSE, vMat.m);
			}

			// Update the shaders with the values of the current object to be rendered
			load_object_shader_values(&objects[k]);

			// Draw the object. The last argument specifiies where OpenGL should
			// start reading the vertecies from in the vbo
			// glBindBuffer(GL_ARRAY_BUFFER, objects[k].vbo);
			// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objects[k].ebo);
			glDrawElements(GL_TRIANGLES, objects[k].eboSize, GL_UNSIGNED_INT, 0);
		}

		// Add to offset so the next loop starts at the correct index
		offset += objectListSizes[vi];
	}

	// Unbind vertex array
	glBindVertexArray(0);
}

void Renderer::render(GLuint* vaos, int numVaos, Camera* camera, Object* objects, int* numObjects) {

	// Clear the screen to bloack
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // WHAT DOES THIS DO??

	// Render all the different objects
	render_objects(vaos, numVaos, objects, numObjects, camera);
}
