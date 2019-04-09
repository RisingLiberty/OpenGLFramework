#version 330 core
// from OpenGL version 3.3 shader version is equal to OpenGL version
// The #version preprocessor directive is used to indicate that the code that follows i GLSL 1.50 code
// using OpenGL's core profile.

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texcoord;

// The color to output to the fragment shader
out vec3 Color;
out vec2 Texcoord;

/* uniform mat4 model;
uniform mat4 view;
uniform mat4 proj; */

// Apart from regular C types, GLSL has built-in vector and matrix types
// identified by vec* and mat* identifiers.
// the values within these constructs is always a float.
// The number after vec specifies the number of components(x,y,z,w) and
// the number after mat specifies the number of rows/columns.
// Since the position attribute consists of only an x and y coordinate, vec2 is perfect
void main()
{
// You can be quite creative when working with vertex types.
// In the example above a shortcuts was used to set the first two components of the vec4
// to those of vec2. the following 2 lines are equal
// gl_Position = vec(position, 0.0f, 1.0f);
// gl_Position = vec(position.x, position.y, 0.0f, 1.0f);
// When you're working with colors, you can also access the individual components with r, g, b and a
// instead of x, y, z and w. this makes no difference and can help with clarity.
// The final position of the vertex assigned to the special gl_Position variable,
// because the position is needed for primitive assembly and many other built-in processes.
// For these to function correctly, the last value w needs to have a value of 1.0f.
// Other than that, you're free to do anything you want with the attributes.
gl_Position =/*  proj * view * model *  */vec4(position, 0.0f, 1.0f);
Color = color;
Texcoord = texcoord;
};