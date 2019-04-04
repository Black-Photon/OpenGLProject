#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoords;

uniform sampler2D ourTexture;
uniform sampler2D otherTexture;

uniform float percent;

void main()
{
    FragColor = mix(texture(ourTexture, TexCoords), texture(otherTexture, TexCoords), percent) * vec4(vertexColor, 1.0f);
}