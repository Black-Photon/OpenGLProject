/**
 * This Post-Processing shader distorts an image horizontally and
 * verically as described by the two lightning textures
 */

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture2D;
uniform sampler1D lightningX;
uniform sampler1D lightningY;

float findLightning(sampler1D tex, float pos);

void main()
{
    float lightningValX = findLightning(lightningX, TexCoords.y);
    float lightningValY = findLightning(lightningY, TexCoords.x);

    // Shift coordinates depending on value
    vec2 newCoords = vec2(TexCoords.x + lightningValX, TexCoords.y + lightningValY);

    FragColor = texture(texture2D, newCoords) * vec4(vec3(1.0), 1.0);
}

float findLightning(sampler1D tex, float pos) {
    float average = 0.0f;
    float size = 1024;
    int number = 10;
    float max = 0.02;
    for (int i = -number/2; i < number/2; i++) {
        float lightningVal = texture(lightningX, pos + i/size).r;
        lightningVal = (lightningVal * 2) - 1;
        if (lightningVal < -max) lightningVal = -max;
        if (lightningVal > max) lightningVal = max;
        average += lightningVal;
    }
    average = average / number;
    return average;
}