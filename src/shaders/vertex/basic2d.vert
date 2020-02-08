/**
 * This Shader simply outputs the shape on a 2d plane at the depth specified
 */

#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform float zPos;

void main()
{
    gl_Position = vec4(aPos, zPos, 1.0);
    TexCoords = aTexCoords;
}