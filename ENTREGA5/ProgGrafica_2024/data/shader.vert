#version 330

// Uniforms
uniform mat4 MVP;
uniform mat4 model;

// Atributos
in vec4 vPos;
in vec4 vColor;
in vec4 vNormal;

// Salidas al fragment shader
out vec4 fColor;
out vec4 fNormal;
out vec4 fPos;

void main() {
	fColor = vColor;
	fNormal = vNormal;
	fPos = vPos;
	gl_Position = MVP * vPos;
}
