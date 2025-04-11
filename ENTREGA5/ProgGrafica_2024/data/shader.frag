#version 330 core

in vec4 fColor;
in vec3 fNormal;
in vec3 fragPos;
in vec2 texCoord;

uniform vec4 lightPos;
uniform vec4 lightColor;
uniform float Ka;
uniform float Kd;
uniform sampler2D myTexture;

out vec4 outColor;

void main()
{
    vec3 norm = normalize(fNormal);
    vec3 lightDir = normalize(vec3(lightPos) - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec4 texColor = texture(myTexture, texCoord);
    vec4 ambient = Ka * texColor;
    vec4 diffuse = Kd * diff * texColor;

    outColor = ambient + diffuse;
}
