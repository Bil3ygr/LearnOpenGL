#pragma once

#ifndef SRC_UTILS_SHADERMANAGER_H_
#define SRC_UTILS_SHADERMANAGER_H_

#include <string>
#include <map>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "singleton.h"

struct ShaderGroup
{
    std::string vsfile;
    std::string fsfile;
    std::string gsfile;

    ShaderGroup(const std::string& _vsfile, const std::string& _fsfile, const std::string& _gsfile = "") :
        vsfile(_vsfile), fsfile(_fsfile), gsfile(_gsfile) {}

    bool operator==(const ShaderGroup& group)
    {
        return vsfile == group.vsfile && fsfile == group.fsfile && gsfile == group.gsfile;
    }
};

class ShaderManager : public Singleton<ShaderManager>
{
    friend class Singleton<ShaderManager>;
private:
    ShaderManager();
    ~ShaderManager() override;

public:
    GLuint GetShaderProgram(const std::string& vsfile, const std::string& fsfile, const std::string& gsfile = "");

    void SetBool(const GLuint& id, const std::string& name, bool value) const;
    void SetInt(const GLuint& id, const std::string& name, int value) const;
    void SetFloat(const GLuint& id, const std::string& name, float value) const;
    void SetVec2(const GLuint& id, const std::string& name, const glm::vec2& value) const;
    void SetVec2(const GLuint& id, const std::string& name, float x, float y) const;
    void SetVec3(const GLuint& id, const std::string& name, const glm::vec3& value) const;
    void SetVec3(const GLuint& id, const std::string& name, float x, float y, float z) const;
    void SetVec4(const GLuint& id, const std::string& name, const glm::vec4& value) const;
    void SetVec4(const GLuint& id, const std::string& name, float x, float y, float z, float w) const;
    void SetMat2(const GLuint& id, const std::string& name, const glm::mat2& mat) const;
    void SetMat3(const GLuint& id, const std::string& name, const glm::mat3& mat) const;
    void SetMat4(const GLuint& id, const std::string& name, const glm::mat4& mat) const;

private:
    GLuint CreateShader(const std::string& filename, const GLuint type);
    void CheckShaderIncludes(const std::string& source);

    std::map<ShaderGroup*, GLuint> shaders_;
    std::map<std::string, std::string> include_shaders_;
};
#endif // !SRC_UTILS_SHADERMANAGER_H_
