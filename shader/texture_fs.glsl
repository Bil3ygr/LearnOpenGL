#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixValue;

void main()
{
    // FragColor = texture(texture0, TexCoord) * vec4(ourColor, 1.0);
    FragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(1.0 - TexCoord.x, TexCoord.y)), clamp(mixValue, 0.0, 1.0));
}
