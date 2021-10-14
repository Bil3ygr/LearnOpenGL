#ifndef DEFINES_LIGHT_
#define DEFINES_LIGHT_

struct DirLight
{
    vec3 direction;

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

uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

vec3 CalcDirLight(vec3 normal, vec3 viewDir, Material material)
{
    vec3 ambient = dirLight.ambient * material.ambient;

    vec3 lightDir = normalize(-dirLight.direction);
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * diff * material.diffuse;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.specular * spec * material.specular;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(vec3 normal, vec3 fragPos, vec3 viewDir, Material material)
{
    vec3 ambient = pointLight.ambient * material.ambient;

    vec3 lightDir = normalize(pointLight.position - fragPos);
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointLight.diffuse * diff * material.diffuse;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLight.specular * spec * material.specular;

    float dist = length(pointLight.position - fragPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * dist + pointLight.quadratic * (dist * dist));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(vec3 normal, vec3 fragPos, vec3 viewDir, Material material)
{
    vec3 ambient = spotLight.ambient * material.ambient;

    vec3 lightDir = normalize(spotLight.position - fragPos);
    float theta = dot(lightDir, normalize(-spotLight.direction));
    vec3 norm = normalize(normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = spotLight.diffuse * diff * material.diffuse;

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLight.specular * spec * material.specular;

    float epsilon = spotLight.cutoff - spotLight.outtercutoff;
    float intensity = clamp((theta - spotLight.outtercutoff) / epsilon, 0.0, 1.0);

    return ambient + diffuse * intensity + specular * intensity;
}

#endif
