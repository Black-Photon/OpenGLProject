#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform vec2 position;
uniform vec2 screen;
uniform vec2 size;

vec2 map(vec2 v, vec2 iMin, vec2 iMax, vec2 oMin, vec2 oMax);

void main()
{
    // Multiplied to 2 means that we can work with whole number coordinates rather than decimals
    vec2 pos = aPos.xy;
    pos = pos * size / screen;
    pos = pos * position / screen;
    gl_Position = vec4(pos, 0.0f, 1.0f);
    TexCoords = aTexCoords;
}