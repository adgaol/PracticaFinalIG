#version 330

layout (location = 0) in vec3 inPosition;
layout (location = 2) in vec3 inNormal;

uniform mat4 uN;
uniform mat4 uM;
uniform mat4 uV;
uniform mat4 uPVM;

out vec3 vN;
out vec3 vpos;

void main() {

    gl_Position = uPVM * vec4(inPosition,1.0);

    vN   = (uN*vec4(inNormal,0.0)).xyz;
    vpos = (uV*uM*vec4(inPosition,1.0)).xyz;

}
