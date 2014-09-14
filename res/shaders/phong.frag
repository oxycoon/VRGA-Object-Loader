#version 150

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
	vec3 halfVector;
	vec3 spotDirection;
	vec3 eyePosition;
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

out vec4 gl_FragColor;

uniform Light light1;
uniform Material material1;

void main(void) {
	//gl_FragColor = vec4(ex_Color,1.0);

	vec3 lightVector = normalize(light1.position);
	vec3 diffuseMaterial = material1.diffuse;
	vec3 specularMaterial = material1.specular;

	vec3 normalVector = normalize(ex_Normal);


	vec3 halfVector = normalize(light1.halfVector);
	//vec3 halfVector = normalize(normalize(light1.eyePosition) - lightVector);

	vec3 diffuse = vec3(max(0.5*dot(normalVector, lightVector), 0.5)) * diffuseMaterial;

	vec3 specular = vec3(max(dot(normalVector, halfVector), 0.0));
	specular = pow(specular.x, material1.shininess) * specularMaterial;

	//gl_FragColor = vec4(ex_Color,1.0);
	gl_FragColor = vec4(diffuse+specular, 1.0);
}
