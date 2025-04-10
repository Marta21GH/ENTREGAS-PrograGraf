#version 330

in vec4 fColor;
in vec4 fNormal;
in vec4 fPos;

uniform vec4 lightPos;
uniform vec4 lightColor;
uniform float Ka;
uniform float Kd;

out vec4 fragColor;

void main() {
	vec3 N = normalize(fNormal.xyz);
	vec3 L = normalize(lightPos.xyz - fPos.xyz);
	float diff = max(dot(N, L), 0.0);

	vec3 color = Ka * fColor.rgb + Kd * diff * fColor.rgb * lightColor.rgb;

	fragColor = vec4(color, 1.0);
}
