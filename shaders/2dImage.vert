#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;
out vec4 p;

uniform vec2 position;
uniform vec2 screen;
uniform vec2 size;

void main()
{
    vec2 pos = aPos;
    pos = pos + vec2(1.0);
    pos = pos * size / screen;
    pos = pos - vec2(1.0);
    pos = pos + 2 * position / screen;
    gl_Position = vec4(pos, 0.0, 1.0);
    TexCoords = aTexCoords;
    p = gl_Position;
}