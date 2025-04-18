#version 330 core

in vec4 fColor;
in vec3 fNorm; //dato vértices
in vec3 fPos;
in vec2 fTextureCoord;

uniform sampler2D textureColor;

//datos variables código
//Variables material objeto
uniform float Kd;
uniform float Ks;
uniform int shinny;

//Variables luz
uniform vec4 lightPos;
uniform vec4 lightColor;
uniform float Ik;

#define DIRECTIONAL 0
#define POINT 1
uniform int lightType;
uniform vec4 lightDirection;

//Variables camara
uniform vec4 cameraPos;

void main() {
	vec4 textureColor = texture(textureColor, fTextureCoord.xy);
	float lightIntensity = 1;
	float ambient = 0.2f;	// CONSTANTE

	float diffuse = 0;
	// IK -> constante intensidad luz
	// KD -> propiedad difusa material
	//  L -> Vector direccion luz
		// Si tipo es DIRECTIONAL, L = lightDirection
		// Si tipo es POINT, L = lightPos - fPos
	vec4 L = vec4(0,0,0,0);
	if(lightType == DIRECTIONAL)
		L = lightDirection;
	else if(lightType == POINT)
		L = normalize(lightPos - fPos);
	//  N -> normal de la superficie
	vec4 N = normalize(fNorm);
	diffuse = Ik * Kd * max(dot(L,N),0);


	float specular = 0;
	//  R -> Rayo luz reflejado de normal
	vec4 R = normalize(reflect(L, N));	//(2(N*L)-L)
	//  V -> Rayo direccion visor/camara
	vec4 V = normalize(fPos - cameraPos);

	specular = Ik * Ks * pow(max(dot(R, V), 0), shinny);

	lightIntensity = specular + ambient + diffuse;

	if(textureColor.a < 0.1) discard;
	gl_FragColor = textureColor * lightIntensity * lightColor;
}