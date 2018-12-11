#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 2) in vec3 inNormal;
layout (location = 3) in vec2 inTexture;

uniform mat4 uN;
uniform mat4 uM;
uniform mat4 uPVM;

out vec3 vN;
out vec3 vpos;
out vec2 vtex;

void main() {

    gl_Position = uPVM * vec4(inPosition,1.0);

    vN   = (uN*vec4(inNormal,0.0)).xyz;
    vpos = (uM*vec4(inPosition,1.0)).xyz;
    vtex = inTexture;

}
