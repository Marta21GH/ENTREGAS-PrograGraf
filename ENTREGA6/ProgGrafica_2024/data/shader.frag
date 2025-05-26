#version 330 core

in vec4 fColor;
in vec3 fNorm;
in vec2 fTexCoord;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 cameraPos;

uniform float Ik;
uniform float Kd;
uniform float Ks;
uniform float shinny;

uniform sampler2D textureColor;

void main() {
    // Normalizado
    vec3 normal = normalize(fNorm);
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Componentes de iluminación
    vec3 ambient = Ik * lightColor;
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = Kd * diff * lightColor;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shinny);
    vec3 specular = Ks * spec * lightColor;

    // Color final combinado
    vec3 lighting = ambient + diffuse + specular;
    vec4 texColor = texture(textureColor, fTexCoord);

    FragColor = vec4(lighting * texColor.rgb, texColor.a);
}
