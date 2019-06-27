#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;
in vec4 FragPosLightSpace;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 viewPos;

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

vec4 average(in vec4 a, in vec4 b)
{
    return (a + b) / 2;
}

void main()
{
    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColour;

    // Ambient
    vec3 ambient = ambientStrength * lightColour;

    // Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;

    // calculate shadow
    float shadow = findShadow(FragPosLightSpace);
    FragColor = vec4((ambient + (1 - shadow) * (diffuse + specular)) * objectColour, 1.0) * texture(utexture, TexCoords);
}