#version 330 core
layout(location = 0) in vec2 vertex_position;
layout(location = 1) in vec2 texture_coords;
out vec2 textCoords;

uniform mat4 modelMat;
uniform mat4 projectionMat;

void main() {
    textCoords = texture_coords;
    gl_Position = projectionMat * modelMat * vec4(vertex_position, 0.0, 1.0);
}