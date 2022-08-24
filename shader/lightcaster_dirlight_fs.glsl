#version 410 core
#extension GL_ARB_shading_language_include : require
#include "/shader/defines_material.glsl"
#include "/shader/defines_light.glsl"

uniform vec3 viewPos;

in vec3 fragPos;
in vec3 normal;
in vec2 TexCoords;

out vec4 fragColor;

void main()
{
    Material m = ConvertLightmapToNormal(lightmapMaterial, TexCoords);
    vec3 result = CalcDirLight(normal, normalize(viewPos - fragPos), m);
    fragColor = vec4(result, 1.0);
}
