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

uniform Material material;
uniform LightmapMaterial lightmapMaterial;

Material ConvertLightmapToNormal(LightmapMaterial m, vec2 texCoords)
{
    Material result;
    result.ambient = vec3(texture(m.diffuse, texCoords));
    result.diffuse = vec3(texture(m.diffuse, texCoords));
    result.specular = vec3(texture(m.specular, texCoords));
    result.shininess = m.shininess;
    return result;
}

#endif
