#version 330

uniform mat4 MVP;	//matriz posiciones globales camara
uniform mat4 M;		//posiciones absolutas para calculos luz
attribute vec4 vPos;	//atributos de entrada de vertices
attribute vec4 vColor;
attribute vec4 vNorm;	//normal a nivel vértice
attribute vec4 vTextureCoord;	//coordenadas textura a nivel vertice

out vec4 fColor; //variable de salida para shader de fragmentos
out vec4 fNorm; //salida datos normales
out vec4 fPos; //salida datos posicion absoluto (sin camara ni proy)
out vec4 fTextureCoord; //salida datos coordenadas textura

void main() {
	//copiar calcular etc. variables de salida
	fColor = vColor;
	gl_Position = MVP * vPos;
	fPos = M * vPos;
	fNorm = inverse(transpose(M)) * vNorm;
	fNorm.w=0;
	fNorm = normalize(fNorm);
	fTextureCoord = vTextureCoord;
}