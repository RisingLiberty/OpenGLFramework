#version 150 core
in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D texHalo;
uniform sampler2D texGoogle;

void main()
{
vec4 colHalo = texture(texHalo, Texcoord);
vec4 colGoogle = texture(texGoogle, Texcoord);

outColor = mix(colHalo, colGoogle, 0.0f);
outColor += vec4(Color, 0.0f);
};