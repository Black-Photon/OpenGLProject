#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoords;

uniform sampler2D ourTexture;
uniform sampler2D otherTexture;

void main()
{
    FragColor = mix(texture(ourTexture, TexCoords), texture(otherTexture, TexCoords), 0.2) * vec4(vertexColor, 1.0f);
}