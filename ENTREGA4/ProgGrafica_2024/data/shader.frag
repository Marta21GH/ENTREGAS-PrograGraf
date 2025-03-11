#version 330
in vec4 fColor;
in vec4 fNorm; // dato de vértices

// datos variables de código
uniform vec4 lightPos;
uniform vec4 lightColor;
uniform vec4 cameraPos;

void main() {
	gl_FragColor = fColor;
}
