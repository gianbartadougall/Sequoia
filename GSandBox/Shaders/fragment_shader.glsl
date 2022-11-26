#version 330 core

in vec3 Colour;

out vec4 outColour;

void main() {
    outColour = vec4(Colour.x, Colour.y, Colour.z, 1.0);
}