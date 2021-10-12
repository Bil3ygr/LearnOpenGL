#version 460 core
out vec4 FragColor;

in vec4 vertexColor;

void main()
{
    // fixed color
    // FragColor = vec4(1.0, 0.5, 0.2, 1.0);

    // color from vertex shader
    FragColor = vertexColor;
}
