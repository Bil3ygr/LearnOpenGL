#version 460 core

uniform bool enableColor;
uniform vec4 color;

in vec4 vertexColor;

out vec4 fragColor;

void main()
{
    if (enableColor)
        fragColor = color;
    else
        fragColor = vertexColor;
}
