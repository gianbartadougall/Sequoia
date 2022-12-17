#version 330 core

in vec3 vertex;
in vec3 colour;

uniform vec3 translation;
uniform vec3 scale;
uniform vec4 rotate;

uniform mat4 projectionMatrix;

out vec3 Colour;

void main() {


    // Rotate vertex. Note rotate is a quaternion => rotate.x = angle and rotate.yzw = axis of rotation
    float theta = rotate.x;
    vec3 rotAxis = 1/length(rotate.yzw) * rotate.yzw;

    // Equation for rotating a point around and axis using quaternions
    vec3 pos = (cos(theta) * vertex) + ((1 - cos(theta)) * dot(rotAxis, vertex) * rotAxis) + (sin(theta) * cross(rotAxis, vertex));
    
    // Translate and scale vertex
    pos = pos + translation;
    pos = vec3(scale.x * pos.x, scale.y * pos.y, scale.z * pos.z);
    
    // Assign the position and the colour
    gl_Position = vec4(pos, 1.0);
    Colour = 0.5 * ((pos + colour));
}