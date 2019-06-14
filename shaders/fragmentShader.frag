#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform vec3 objectColour;
uniform vec3 lightColour;
uniform vec3 viewPos;

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
    vec3 diffuse = diff * lightColour;

    // Ambient
    vec3 ambient = ambientStrength * lightColour;

    // Specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;

    FragColor = vec4((ambient + diffuse + specular) * objectColour, 1.0f);
    //FragColor = vec4(vec3(pow(gl_FragCoord.z, 10)), 1.0f);
}