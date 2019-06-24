#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TexCoords;

uniform float ambientStrength;
uniform float diffuseStrength;
uniform float specularStrength;
uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 viewPos;
uniform float exposure;

uniform sampler2D utexture;

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

    FragColor = vec4((ambient + diffuse + specular - vec3(exposure) * 0.5) * objectColour, 1.0) * texture(utexture, TexCoords);
}