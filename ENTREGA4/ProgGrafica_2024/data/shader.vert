#version 330

uniform mat4 MVP;
attribute vec4 vPos;
attribute vec4 vColor;
attribute vec4 vNorm;

out vec4 fColor;

void main() {
	fColor = vColor;
	gl_Position = MVP * vPos;
}