/**
 * This shader transforms a point to model space, then view, then final,
 * while outputting useful position values
 */

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool inside;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    TexCoords = vec2(aTexCoords.x, 1.0 - aTexCoords.y);
    FragPos = (model * vec4(aPos, 1.0)).xyz;
    if(inside) Normal = -aNormal;
    else Normal = aNormal;
}