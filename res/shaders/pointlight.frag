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
in vec3 ex_ecPos;

uniform Light light1;
uniform Material material1;

out vec4 gl_FragColor;

void main(void) {
	vec3 n, halfV, viewV, lightDir;
	float NdotL, NdotHV;
	vec3 ambient, specular, diffuse;
	float att, lightDist;

	lightDir = vec3(light1.position - ex_ecPos);
	lightDist = length(light1.position);
	ambient = light1.ambient * material1.ambient;
	specular = light1.specular * material1.specular;
	diffuse = light1.diffuse * material1.diffuse;
	
	vec4 color = vec4(ambient, 1.0) + 0.0001*ex_Color;//ex_color is a hack

	n = normalize(ex_Normal);

	NdotL = max(dot(n,normalize(lightDir)),0.0);

	if(NdotL > 0.0)
	{
		att = 1 / (light1.constantAttenuation + light1.linearAttenuation * lightDist +
				light1.quadraticAttenuation * lightDist * lightDist);
		color += att * (diffuse * NdotL + ambient);

		NdotHV = max(dot(n,halfV),0.0);
		color += att * vec4(specular,1.0) * pow(NdotHV, material1.shininess);		
	}


	gl_FragColor = color;
}
