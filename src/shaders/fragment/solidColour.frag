/**
 * This shader simply outputs the input colour uniform
 */

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec4 colour;

void main()
{
    FragColor = colour;
}