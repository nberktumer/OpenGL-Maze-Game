#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexture;

out vec2 coord;

uniform mat4 Projection, Model, View;

void main() {
    gl_Position = Projection * View * Model * vPosition;
    coord = vTexture;
}