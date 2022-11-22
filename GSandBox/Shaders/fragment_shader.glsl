#version 330 core

in vec3 Colour;

out vec4 outColour;

void main() {
    outColour = vec4(1.0 - Colour.x, 1.0 - Colour.y, 1 - Colour.z, 1.0);
}