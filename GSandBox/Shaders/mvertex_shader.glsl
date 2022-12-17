#version 330 core

in vec3 vertex;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;

out vec3 Colour;

void main() {

    // Assign the position and the colour
    Colour = 0.5 * (vertex + vec3(1, 1, 1));

    gl_Position = projectionMatrix * viewMatrix * transformationMatrix * vec4(vertex, 1.0);
}