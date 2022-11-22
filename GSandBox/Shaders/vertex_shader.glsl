#version 330 core

in vec3 position;
in vec3 colour;

uniform mat4 transformation;

out vec3 Colour;

void main() {
    Colour = colour;
    gl_Position = transformation * vec4(position, 1.0);
}