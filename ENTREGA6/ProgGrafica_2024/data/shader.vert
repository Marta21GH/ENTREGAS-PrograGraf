#version 330 core

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec3 vNorm;
layout(location = 3) in vec2 vTextureCoord;

out vec4 fColor;
out vec3 fNorm;
out vec2 fTexCoord;
out vec3 fragPos;

uniform mat4 M;
uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vPos, 1.0);
    fColor = vColor;
    fNorm = normalize(mat3(M) * vNorm);
    fragPos = vec3(M * vec4(vPos, 1.0));
    fTexCoord = vTextureCoord;
}
