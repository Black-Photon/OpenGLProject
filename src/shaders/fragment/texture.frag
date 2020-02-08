/**
 * This shader simply outputs the input
 */

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture2D;

void main()
{
    FragColor = texture(texture2D, TexCoords);
}