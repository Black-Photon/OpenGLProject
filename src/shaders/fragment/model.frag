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

struct Shadow {
    samplerCube depthMap;
    float far_plane;
};

uniform Shadow shadow_in;

uniform bool usesNormalMap;

// ------------------------------------------------------------------------
// --                    PROTOTYPES + VARIABLES                          --
// ------------------------------------------------------------------------

vec4 calculateAmbient();
vec4 calculateDiffuse(vec3 Normal, Light light);
vec4 calculateSpecular(vec3 Normal, Camera camera, Light light);
float calculateShadow(Shadow shadow);

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

vec3 gridSamplingDisk[20] = vec3[]
(
vec3(1, 1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1, 1,  1),
vec3(1, 1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
vec3(1, 1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1, 1,  0),
vec3(1, 0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1, 0, -1),
vec3(0, 1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0, 1, -1)
);

vec3 NormalMap;

// ------------------------------------------------------------------------
// --                         MAIN FUNCTIONS                             --
// ------------------------------------------------------------------------


void main() {
    if (usesNormalMap) NormalMap = texture(material.texture_normal1, TexCoords).xyz;
    else NormalMap = Normal;

    vec4 ambient = calculateAmbient();
    vec4 diffuse = calculateDiffuse(NormalMap, light);
    vec4 specular = calculateSpecular(NormalMap, camera, light);
    float shadow = calculateShadow(shadow_in);

    float distance = distanceBetween(camera.position, light.position);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.031 * (distance * distance));

    FragColor = ambient + attenuation * (1 - shadow) * (diffuse + specular);
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

float calculateShadow(Shadow shadow) {
    vec3 fragToLight = FragPos - light.position;
    float currentDepth = length(fragToLight);

    float shadowVal = 0.0;
    float bias = 0.01;
    int samples = 20;

    float viewDistance = length(camera.position - FragPos);
    float diskRadius = (1.0 + (viewDistance / shadow.far_plane)) / 100.0;

    for(int i = 0; i < samples; i++) {
        float closestDepth = texture(shadow.depthMap, fragToLight + gridSamplingDisk[i] * diskRadius).r;
        closestDepth *= shadow.far_plane;
        if(currentDepth - bias > closestDepth)
        shadowVal += 1.0;
    }
    shadowVal /= float(samples);

    return shadowVal;
}

float distanceBetween(vec3 first, vec3 second) {
    vec3 difference = second - first;
    return sqrt(difference.x*difference.x + difference.y*difference.y + difference.z*difference.z);
}