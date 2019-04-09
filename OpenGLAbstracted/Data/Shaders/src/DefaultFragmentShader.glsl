#version 150 core
// You'll immediately notice that we're not using some built-in variable for outputting the color, say gl_FragColor.
// This is because a fragment shader can in fact output multiple colors.
// The outColor variable uses the type vec4, because each color consists of a red, green, blue and alpha component.
// Colors in OpenGL are generally represented as floating point number between 0.0 and 1.0 instead of the common 0 and 255.

// Vertex attributes are not the only way to pass data to shader programs. There is another way to pass data to shaders called uniforms.
// These are essentially global variables, having the same value for all vertices and/or fragments.
in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

//uniform sampler2D texHalo;
//uniform sampler2D texGoogle;

void main()
{
//vec4 colHalo = texture(texHalo, Texcoord);//  * vec4(Color, 1.0f);
//vec4 colGoogle = texture(texGoogle, Texcoord);//  * vec4(Color, 1.0f);

// the mix function is a special GLSL function that linearly interpolates between 2 variables based on the third parameter.
// A value of 0.0 will result in the first value, a value of 1.0 will result in the second value and a value in between will
// result in a mixture of both.
//outColor = mix(colHalo, colGoogle, 0.5f);
vec3 finalColor = Color * vec3(Texcoord, 1.0f);

outColor = vec4(finalColor, 1.0f);
};