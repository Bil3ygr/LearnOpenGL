#version 410 core

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform bool mixEnable;
uniform float mixValue;
uniform vec4 mixColor;

in vec2 TexCoord;

out vec4 fragColor;

void main()
{
    if (mixEnable)
        fragColor = mix(texture(texture0, TexCoord), texture(texture1, vec2(1.0 - TexCoord.x, TexCoord.y)), clamp(mixValue, 0.0, 1.0));
    else
        fragColor = texture(texture0, TexCoord);

    fragColor = fragColor * mixColor;
}
