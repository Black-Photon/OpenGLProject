#version 330 core
out vec4 FragColor;

in vec4 FragPosLightSpace;

uniform int alpha;

uniform sampler2D utexture;
uniform sampler2D shadowMap;

float findShadow(vec4 fragPosLightSpace) {
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform [-1, 1] to [0, 1]
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;

    float bias = 0.01;
    // check whether current frag pos is in shadow
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -5; x <= 5; ++x)
    {
        for(int y = -5; y <= 5; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 121.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    // calculate shadow
    float shadow = findShadow(FragPosLightSpace);
    FragColor = vec4((0.2 + 0.8 * (1 - shadow)) * vec3(0.1, 0.3, 1.0), alpha);
}