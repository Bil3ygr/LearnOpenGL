#ifndef DEFINES_MATERIAL_
#define DEFINES_MATERIAL_

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct LightmapMaterial
{
    sampler2D diffuse;
    sampler2D specular;
    // vec3 specular;
    float shininess;
};

#endif
