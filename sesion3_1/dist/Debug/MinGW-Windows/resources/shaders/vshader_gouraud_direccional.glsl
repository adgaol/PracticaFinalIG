#version 330

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

#define NLD 1

layout (location = 0) in vec3 inPosition;
layout (location = 2) in vec3 inNormal;

uniform mat4 uN;
uniform mat4 uM;
uniform mat4 uV;
uniform mat4 uPVM;

uniform Light    lightG;
uniform Light    lightD[NLD];
uniform Material material;

out vec4 vcolor;

vec4 funDirectional(Light light, vec3 N, vec3 V);

void main() {

    gl_Position = uPVM * vec4(inPosition,1.0);

    vcolor = lightG.ambient * material.ambient;
    
    vec3  vpos = (uV*uM*vec4(inPosition.xyz,1.0)).xyz;

    vec3  N = normalize((uN*vec4(inNormal,0.0)).xyz);
    vec3  V = normalize(-vpos);

    vcolor += funDirectional(lightD[0],N,V);

}

vec4 funDirectional(Light light, vec3 N, vec3 V) {

    vec3  L = normalize(light.direction);
    vec3  R = normalize(reflect(-L,N));

    float dotLN = dot(L,N);
    float dotRV = clamp(dot(R,V), 0.0, 1.0);

    vec4  ambient  =       light.ambient  * material.ambient;
    vec4  diffuse  = clamp(light.diffuse  * material.diffuse  * dotLN                        , 0.0, 1.0);
    vec4  specular = clamp(light.specular * material.specular * pow(dotRV,material.shininess), 0.0, 1.0);

    vec4 color = ambient + diffuse + specular;

    return color;

}
