#version 150

precision highp float;

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	vec3 halfVector;
	vec3 spotDirection;
	float spotExponent;
	float spotCutoff;
	float spotCosCutoff;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

struct Material
{
	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 in_Position;
in vec3 in_Color;
in vec3 in_Normal;

uniform mat4 mvpmatrix;
uniform Light light1;
uniform Material material1;

out vec3 ex_Color;
out vec3 ex_Normal;
out Light ex_Light;
out Material ex_Material;

void main(void) {
	vec3 norm = normalize(in_Normal);
	vec3 lightDir = normalize(light1.position);
	float NdotL;
	
	NdotL = max(dot(norm, lightDir), 0.0);

	vec3 ambient = light1.ambient * in_Color;

	ex_Normal = in_Normal;
	ex_Color = in_Color * light1.diffuse;
	ex_Color = ex_Color * NdotL + ambient;
	ex_Material = material1;
	ex_Light = light1;

	gl_Position = mvpmatrix * vec4(in_Position, 1.0);
}
