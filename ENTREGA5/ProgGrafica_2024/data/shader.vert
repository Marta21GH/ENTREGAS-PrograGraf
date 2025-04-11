#version 330 core

in vec4 vPos;
in vec4 vColor;
in vec4 vNormal;
in vec4 vTextureCoord;

uniform mat4 MVP;
uniform mat4 model;

out vec4 fColor;
out vec3 fNormal;
out vec3 fragPos;
out vec2 texCoord;

void main()
{
    gl_Position = MVP * vPos;
    fColor = vColor;
    fNormal = mat3(model) * vNormal.xyz; // normal transform
    fragPos = vec3(model * vPos);        // world position
    texCoord = vTextureCoord.xy;         // passthrough texture coord
}
