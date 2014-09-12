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

out vec4 ex_Color;

void main(void) {
// Multiply the mvp matrix by the vertex to obtain our final vertex position
    	gl_Position = mvpmatrix * vec4(in_Position, 1.0);
    	float NdotL;
	
	vec3 lightDirection = normalize(light1.position);
	vec3 diffuse = material1.diffuse * light1.diffuse+0.0001*in_Color; // hack to make it work
	vec3 ambient = material1.ambient * light1.ambient;
	vec3 specular = vec3(0.0,0.0,0.0);

	NdotL = max(dot(normalize(lightDirection), in_Normal), 0.0);

	vec3 eyeVector = light1.halfVector;

	if(NdotL > 0.0)
	{
		vec3 halfVector = normalize(normalize(eyeVector) - lightDirection);
		float NdotHV = max(dot(in_Normal, halfVector),0.0);
		specular = material1.specular * light1.specular * pow(NdotHV,material1.shininess);
	}

	ex_Color = vec4(diffuse*NdotL, 1) + vec4(ambient,1) + vec4(specular,1);
}

