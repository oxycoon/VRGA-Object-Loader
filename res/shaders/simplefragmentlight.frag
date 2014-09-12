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


in vec4 ex_Color;
in vec3 ex_Normal;

uniform Light light1;
uniform Material material1;

out vec4 gl_FragColor;

void main(void) {
	vec3 n, lightDir;
	float NdotL, NdotHV;
	vec3 ambient, specular, diffuse;

	lightDir = vec3(normalize(light1.position));
	ambient = light1.ambient * material1.ambient;
	specular = light1.specular * material1.specular;
	diffuse = light1.diffuse * material1.diffuse;
	
	vec4 color = vec4(ambient, 1.0) + 0.0001*ex_Color;//ex_color is a hack

	n = normalize(ex_Normal);

	NdotL = max(dot(n,lightDir),0.0);

	if(NdotL > 0.0)
	{
		color += vec4(diffuse * NdotL, 1.0);
		NdotHV = max(dot(n,light1.halfVector),0.0);
		color += vec4(specular,1.0) * pow(NdotHV, material1.shininess);		
	}


	gl_FragColor = color;
}
