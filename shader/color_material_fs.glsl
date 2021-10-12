#version 460 core
#extension GL_ARB_shading_language_include : require
#include "/shader/defines_material.glsl"
#include "/shader/defines_light.glsl"

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

void main()
{
    vec3 ambient = light.ambient * material.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
