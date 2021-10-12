#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;
uniform float offsetY;

void main()
{
    gl_Position = vec4(abs(aPos.x - 1.0), abs(aPos.y - 1.0) + offsetY, aPos.z, 1.0);
    // vertexColor = vec4(aColor, 1.0);
    vertexColor = gl_Position;
}
