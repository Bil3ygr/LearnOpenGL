#version 460 core

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixValue;

in vec3 ourColor;
in vec2 TexCoord;

out vec4 fragColor;

void main()
{
    // FragColor = texture(texture0, TexCoord) * vec4(ourColor, 1.0);
    fragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(1.0 - TexCoord.x, TexCoord.y)), clamp(mixValue, 0.0, 1.0));
}
