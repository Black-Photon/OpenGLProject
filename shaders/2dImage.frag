#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D utexture;

void main()
{
    FragColor = texture(utexture, TexCoords);
    FragColor = textureLod(utexture, TexCoords, 10);
//    FragColor = vec4(TexCoords, 1.0f, 1.0f);
}