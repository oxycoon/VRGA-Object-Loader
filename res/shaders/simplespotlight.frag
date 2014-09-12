#version 150

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


in vec3 ex_Color;
in vec3 ex_Normal;
in Light ex_Light;
in Material ex_Material;

out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = vec4(ex_Color, 1.0);
}
