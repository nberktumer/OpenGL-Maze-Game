#version 410

in vec2 coord;

out vec4 fragColor;

uniform sampler2D textureSampler;

void main() {
    fragColor = texture2D(textureSampler, coord);
}

