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
#define NLP 2
#define NLF 2

in vec3 vN;
in vec3 vpos;
in vec2 vtex;

uniform vec3     uposc;
uniform Light    ulightG;
uniform Light    ulightD[NLD];
uniform Light    ulightP[NLP];
uniform Light    ulightF[NLF];
uniform Material umaterial;

uniform sampler2D utex;
uniform float     umixValue;

out vec4 outColor;

vec4 funDirectional(Light light, Material material, vec3 N, vec3 V);
vec4 funPositional (Light light, Material material, vec3 N, vec3 V);
vec4 funFocal      (Light light, Material material, vec3 N, vec3 V);

void main() {

    vec3  N = normalize(vN);
    vec3  V = normalize(uposc - vpos);

    outColor = ulightG.ambient * umaterial.ambient;

    for(int i=0; i<NLD; i++) outColor += funDirectional(ulightD[i],umaterial,N,V);
    for(int i=0; i<NLP; i++) outColor += funPositional (ulightP[i],umaterial,N,V);
    for(int i=0; i<NLF; i++) outColor += funFocal      (ulightF[i],umaterial,N,V);

}

vec4 funDirectional(Light light, Material material, vec3 N, vec3 V) {

    vec3  L = normalize(-light.direction);
    vec3  R = normalize(reflect(-L,N));

    float dotLN = dot(L,N);
    float dotRV = clamp(dot(R,V), 0.0, 1.0);

    vec4  ambient  =       light.ambient  * material.ambient;
    vec4  diffuse  = clamp(light.diffuse  * material.diffuse  * dotLN                        , 0.0, 1.0);
    vec4  specular = clamp(light.specular * material.specular * pow(dotRV,material.shininess), 0.0, 1.0);

    return mix(ambient + diffuse, texture(utex,vtex), umixValue) + specular;

}

vec4 funPositional(Light light, Material material, vec3 N, vec3 V) {

    vec3  L = normalize(light.position - vpos);   
    vec3  R = normalize(reflect(-L,N));

    float dotLN = dot(L,N);
    float dotRV = clamp(dot(R,V), 0.0, 1.0);

    vec4  ambient  =       light.ambient  * material.ambient;
    vec4  diffuse  = clamp(light.diffuse  * material.diffuse  * dotLN                        , 0.0, 1.0);
    vec4  specular = clamp(light.specular * material.specular * pow(dotRV,material.shininess), 0.0, 1.0);

    float distance    = length(light.position  - vpos);
    float attenuation = 1.0/(light.c0 + light.c1*distance + light.c2*pow(distance,2));

    return attenuation*(mix(ambient + diffuse, texture(utex,vtex), umixValue) + specular);

}

vec4 funFocal(Light light, Material material, vec3 N, vec3 V) {

    vec3  L = normalize(light.position - vpos);    
    vec3  R = normalize(reflect(-L,N));

    float dotLN = dot(L,N);
    float dotRV = clamp(dot(R,V), 0.0, 1.0);

    vec4  ambient  =       light.ambient  * material.ambient;
    vec4  diffuse  = clamp(light.diffuse  * material.diffuse  * dotLN                        , 0.0, 1.0);
    vec4  specular = clamp(light.specular * material.specular * pow(dotRV,material.shininess), 0.0, 1.0);

    float distance    = length(light.position - vpos);
    float attenuation = 1.0/(light.c0 + light.c1*distance + light.c2*pow(distance,2));

    vec3  direction   = normalize(-light.direction); 
    float intensity   = clamp((dot(L,direction) - light.outerCutOff)/(light.innerCutOff - light.outerCutOff), 0.0f, 1.0f);

    return attenuation*(mix(ambient + intensity*diffuse, texture(utex,vtex), umixValue) + intensity*specular);

}
