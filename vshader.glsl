#version 410

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexture;

out vec3 fN;
out vec3 fV;
out vec3 fL;
out vec2 coord;

uniform mat4 Projection, Model, View, LightLocation;
uniform vec4 LightPosition;

void main() {
    vec4 lightPosition = LightLocation * LightPosition;
    vec3 pos = (View * Model * vPosition).xyz;

    fN = (View * Model * vec4(vNormal, 0.0)).xyz; // normal direction in camera coordinates
    fV = -pos; //viewer direction in camera coordinates
    fL = lightPosition.xyz; // light direction

    if( LightPosition.w != 0.0 ) {
        fL = lightPosition.xyz - pos;  //directional light source
    }
    gl_Position = Projection * View * Model * vPosition;
    coord = vTexture;
}