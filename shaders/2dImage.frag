#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D utexture;

void main()
{
    FragColor = texture(utexture, TexCoords);
}