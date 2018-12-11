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

#define NLD 1

in vec3 vN;
in vec3 vpos;

uniform vec4     lightG;
uniform Light    lightD[NLD];
uniform Material material;

out vec4 outColor;

vec4 funDirectional(Light light, vec3 N, vec3 V);

void main() {

    vec3  N = normalize(vN);
    vec3  V = normalize(-vpos);

    outColor = lightG * material.ambient;

    outColor += funDirectional(lightD[0],N,V);

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
