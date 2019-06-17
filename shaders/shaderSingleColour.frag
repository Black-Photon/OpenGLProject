#version 330 core
out vec4 FragColor;

uniform int alpha;

void main()
{
    FragColor = vec4(0.1, 0.3, 1.0, alpha);
}