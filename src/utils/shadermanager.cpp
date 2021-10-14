#include "utils/shadermanager.h"

#include <set>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "utils/helper.h"

// #define INCLUDE_DEBUG

ShaderManager::ShaderManager()
{
    shaders_ = std::map<ShaderGroup*, GLuint>();
    include_shaders_ = std::map<std::string, std::string>();
}

ShaderManager::~ShaderManager()
{
    for (auto iter = shaders_.begin(); iter != shaders_.end(); ++iter)
    {
        delete iter->first;
        glDeleteProgram(iter->second);
    }
    shaders_.clear();
    include_shaders_.clear();
}

GLuint ShaderManager::GetShaderProgram(const std::string& vsfile, const std::string& fsfile, const std::string& gsfile)
{
    ShaderGroup* group = new ShaderGroup(vsfile, fsfile, gsfile);
    auto iter = shaders_.find(group);
    if (iter != shaders_.end())
        return iter->second;

    GLuint program = 0;
    GLuint vertexShader = CreateShader(vsfile, GL_VERTEX_SHADER);
    if (vertexShader)
    {
        GLuint fragmentShader = CreateShader(fsfile, GL_FRAGMENT_SHADER);
        if (fragmentShader)
        {
            GLuint geometryShader = 0;
            if (!gsfile.empty())
                geometryShader = CreateShader(gsfile, GL_GEOMETRY_SHADER);

            program = glCreateProgram();
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            if (geometryShader)
                glAttachShader(program, geometryShader);
            glLinkProgram(program);

            int success;
            char infoLog[512];
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (success)
            {
                shaders_.emplace(group, program);
            }
            else
            {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                ERROR("Compile shader error: %s\n", &infoLog);
                glDeleteProgram(program);
                program = 0;
            }

            if (geometryShader)
                glDeleteShader(geometryShader);

            glDeleteShader(fragmentShader);
        }
        glDeleteShader(vertexShader);
    }
    return program;
}

void ShaderManager::SetBool(const GLuint& id, const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void ShaderManager::SetInt(const GLuint& id, const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void ShaderManager::SetFloat(const GLuint& id, const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

 void ShaderManager::SetVec2(const GLuint& id, const std::string& name, const glm::vec2& value) const
 {
     glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
    //  glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
 }

void ShaderManager::SetVec2(const GLuint& id, const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}

 void ShaderManager::SetVec3(const GLuint& id, const std::string& name, const glm::vec3& value) const
 {
     glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
    //  glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
 }

void ShaderManager::SetVec3(const GLuint& id, const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

 void ShaderManager::SetVec4(const GLuint& id, const std::string& name, const glm::vec4& value) const
 {
     glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, glm::value_ptr(value));
    //  glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
 }

void ShaderManager::SetVec4(const GLuint& id, const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

 void ShaderManager::SetMat2(const GLuint& id, const std::string& name, const glm::mat2& mat) const
 {
     glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    //  glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
 }

 void ShaderManager::SetMat3(const GLuint& id, const std::string& name, const glm::mat3& mat) const
 {
     glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    //  glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
 }

 void ShaderManager::SetMat4(const GLuint& id, const std::string& name, const glm::mat4& mat) const
 {
     glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
    //  glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
 }

GLuint ShaderManager::CreateShader(const std::string& filename, const GLuint shaderType)
{
    const char* shaderSource = ReadFile(filename.c_str());
    if (!shaderSource)
        return 0;

    GLuint shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    CheckShaderIncludes(std::string(shaderSource));
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        ERROR("Compile shader error: %s\n", &infoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

#define INCLUDE_KEY "#include"
#define FILE_KEY "\""
#define COMMENT_KEY "//"

void ShaderManager::CheckShaderIncludes(const std::string& source)
{
    // find includes
    std::vector<std::string> includes;
    size_t offset = 0;
    size_t include_flag_idx = source.find(INCLUDE_KEY, offset);
    while (include_flag_idx != -1)
    {
        size_t char1_flag = source.find(FILE_KEY, include_flag_idx + 8);
        size_t char2_flag = source.find(FILE_KEY, char1_flag + 1);
        if (char1_flag == -1 || char2_flag == -1)
        {
#ifdef INCLUDE_DEBUG
            ERROR("include found, but quotes not found, please check glsl file\n");
#endif
        }
        else
        {
            std::string include_file_name = source.substr(char1_flag + 1, char2_flag - char1_flag - 1);
            includes.emplace_back(include_file_name);
        }
        offset = char2_flag;
        include_flag_idx = source.find(INCLUDE_KEY, offset);
    }

    if (includes.empty())
        return;

    // set includes
    std::set<std::string> names;
    for (size_t i = 0; i < includes.size(); i++)
    {
        std::string name = includes[i];
        if (names.find(name) != names.end())
        {
#ifdef INCLUDE_DEBUG
            WARNING("file [%s] already include\n", name.c_str());
#endif
            continue;
        }
        auto iter = include_shaders_.find(name);
        if (iter != include_shaders_.end())
        {
            glNamedStringARB(
                GL_SHADER_INCLUDE_ARB,
                name.size(), name.c_str(),
                iter->second.size(), iter->second.c_str()
            );
        }
        else
        {
            const char* file_data = ReadFile(("." + name).c_str());
            if (!file_data)
                continue;
            glNamedStringARB(
                GL_SHADER_INCLUDE_ARB,
                name.size(), name.c_str(),
                std::string(file_data).size(), file_data
            );
            names.emplace(name);
            include_shaders_[name] = std::string(file_data);
        }
    }
}
