#version 330 core

struct Light {
    vec3  position;
    vec3  direction;
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    float innerCutOff;
    float outerCutOff;
    float c0;
    float c1;
    float c2;
};

struct Material {
    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    float shininess;
};

layout (location = 0) in vec3 inPosition;

uniform mat4 uPVM;

uniform Light    lightG;
uniform Material material;

out vec4 vColor;

void main() {

    gl_Position = uPVM * vec4(inPosition,1);

    vColor = lightG.ambient * material.ambient;
	
}
