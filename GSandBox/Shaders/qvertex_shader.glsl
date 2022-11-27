#version 330 core

in vec3 position;
in vec3 colour;

uniform vec3 translation;
uniform vec3 scale;
uniform vec4 rotate;

out vec3 Colour;

void main() {

    // Translate and scale position
    vec3 pos = position + translation;
    pos = vec3(scale.x * pos.x, scale.y * pos.y, scale.z * pos.z);

    // Rotate position. Note rotate is a quaternion => rotate.x = angle and rotate.yzw = axis of rotation
    float theta = rotate.x;
    vec3 rotAxis = 1/length(rotate.yzw) * rotate.yzw;

    // Equation for rotating a point around and axis using quaternions
    pos = (cos(theta) * pos) + ((1 - cos(theta)) * dot(rotAxis, pos) * rotAxis) + (sin(theta) * cross(rotAxis, pos));
    
    // Assign the position and the colour
    gl_Position = vec4(pos, 1.0);
    Colour = vec3(pos.xyz);
}