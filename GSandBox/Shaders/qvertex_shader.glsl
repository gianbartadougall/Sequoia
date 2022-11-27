#version 330 core

in vec3 position;
in vec3 colour;

uniform vec3 translation;
uniform vec3 scale;
uniform vec4 rotate;

uniform mat4 transformation;
uniform float theta;
uniform mat4 projectionMatrix;

out vec3 Colour;

void main() {
    vec3 r = rotate.yzw;
    float norm = 1/length(r);

    // Calculate the unit vector for the axis of rotation 
    vec3 u = vec3(norm * r.x, norm * r.y, norm * r.z);
    
    float theta = rotate.x;
    vec3 pos = (cos(theta) * position) + ((1 - cos(theta)) * dot(u, position) * u) + (sin(theta) * cross(u, position));
    gl_Position = vec4(pos, 1.0f);
    vec4 pos1 = (vec4(pos, 1.0) + vec4(translation, 0));
    gl_Position = vec4(scale.x * pos1.x, scale.y * pos1.y, scale.z * pos1.z, pos1.w);
    Colour = vec3(pos1.xyz);
}