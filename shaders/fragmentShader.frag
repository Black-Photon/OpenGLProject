#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D ourTexture;
uniform sampler2D otherTexture;

uniform float percent;

void main()
{
    FragColor = mix(texture(ourTexture, TexCoords), texture(otherTexture, TexCoords), percent);
}