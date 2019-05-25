#version 410

in vec4 vPosition;
in vec3 vNormal;
out vec4 color;

uniform mat4 Projection, Model, View;
uniform vec4 Color;

void main()
{
    gl_Position = Projection * View * Model * vPosition;
    color = Color;
}