#version 330 core

in vec3 position;
in vec3 colour;

// uniform vec3 translation;
// uniform vec3 scale;
// uniform vec4 rotate;

uniform vec3 cameraRotation;
uniform vec3 cameraPosition;
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

out vec3 Colour;

void main() {

    // Apply transformation
    vec4 vertex = transformationMatrix * vec4(position, 1.0);
    vec4 vertex1 = vec4(vertex.xyz - cameraPosition, 1.0);

    // Apply rotation. Calculate the vector perpendicular to the orientation vector
    vec3 rotAxis = vec3(0, -1, 0); // Normalise the rotation axis

    // Calculate angle of rotation from the orientation of the camera
    float theta = cameraRotation.y;

    // Equation for rotating a point around and axis using quaternions
    vec3 pos = (cos(theta) * vertex1.xyz) + ((1 - cos(theta)) * dot(rotAxis, vertex1.xyz) * rotAxis) + (sin(theta) * cross(rotAxis, vertex1.xyz));

    // Rotation axis in phi is always the x axis because the screen always points torwards the -z. Everything gets rotated to face that way. So no matter what, you always face -z
    // so to rotate up and down, you need to rotate about x axis
    vec3 rotAxis1 = vec3(-1, 0, 0);
    theta = cameraRotation.x;
    pos = (cos(theta) * pos) + ((1 - cos(theta)) * dot(rotAxis1, pos) * rotAxis1) + (sin(theta) * cross(rotAxis1, pos));

    // Assign the position and the colour
    gl_Position = projectionMatrix * vec4(pos, 1.0);
    Colour = colour; 
    //vertex.xyz;
}