#version 330 core

in vec3 position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformationMatrix;

out vec3 Colour;

void main() {

    // Assign the position and the colour
    Colour = 0.5 * (position + vec3(1, 1, 1));

    gl_Position = projectionMatrix * transformationMatrix * vec4(position, 1.0);
}