#ifndef DEFINES_LIGHT_
#define DEFINES_LIGHT_

struct Light
{
    vec4 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outtercutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#endif
