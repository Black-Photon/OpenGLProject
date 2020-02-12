/**
 * This shader displays the final scene using graphical techniques
 */

#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

// ------------------------------------------------------------------------
// --                            UNIFORMS                                --
// ------------------------------------------------------------------------

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
};

uniform Material material;

struct Light {
    vec3 position;
    vec3 colour;
    float intensity;
};

uniform Light light;

struct Camera {
    vec3 viewDir;
    vec3 position;
};

uniform Camera camera;

uniform bool usesNormalMap;

// ------------------------------------------------------------------------
// --                    PROTOTYPES + VARIABLES                          --
// ------------------------------------------------------------------------

vec4 calculateAmbient();
vec4 calculateDiffuse(vec3 Normal, Light light);
vec4 calculateSpecular(vec3 Normal, Camera camera, Light light);

vec4 mkVec4(float i) {
    return vec4(vec3(i), 1.0);
}

vec4 resetAlpha(vec4 i) {
    return vec4(i.xyz, 1.0);
}

float distanceBetween(vec3 first, vec3 second);

float ambientLimit = 0.4;
float diffuseLimit = 0.8;
float specularLimit = 8.0;

vec3 normalMap;

// ------------------------------------------------------------------------
// --                         MAIN FUNCTIONS                             --
// ------------------------------------------------------------------------


void main() {
    if (usesNormalMap) normalMap = texture(material.texture_normal1, TexCoords).xyz;
    else normalMap = Normal;

    vec4 ambient = calculateAmbient();
    vec4 diffuse = calculateDiffuse(normalMap, light);
    vec4 specular = calculateSpecular(normalMap, camera, light);

    float distance = distanceBetween(camera.position, light.position);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.031 * (distance * distance));

    FragColor = ambient + attenuation * (diffuse + specular);
}

vec4 calculateAmbient() {
    vec4 ambient = ambientLimit * texture(material.texture_diffuse1, TexCoords);
    ambient = resetAlpha(ambient);

    return ambient;
}

vec4 calculateDiffuse(vec3 Normal, Light light) {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diffuse = max(dot(norm, lightDir), 0.0) * diffuseLimit;

    vec4 diffuseVec = diffuse * texture(material.texture_diffuse1, TexCoords);
    diffuseVec = resetAlpha(diffuseVec);

    return diffuseVec;
}

vec4 calculateSpecular(vec3 Normal, Camera camera, Light light) {
    vec3 lightDir   = normalize(light.position - FragPos);
    vec3 viewDir    = normalize(camera.position - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(min(max(dot(Normal, halfwayDir), 0.0), 1.0), 32);
    spec = specularLimit * spec;

    vec4 specular = spec * texture(material.texture_specular1, TexCoords);
    specular = resetAlpha(specular);

    return specular;
}

float distanceBetween(vec3 first, vec3 second) {
    vec3 difference = second - first;
    return sqrt(difference.x*difference.x + difference.y*difference.y + difference.z*difference.z);
}