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

precision highp float;

in vec3 in_Position;
in vec3 in_Color;
in vec3 in_Normal;

// mvpmatrix is the result of multiplying the model, view, and projection matrices */
uniform mat4 mvpmatrix;
uniform Light light1;
uniform Material material1;

out vec3 ex_Color;
out vec3 ex_Normal;
out float ex_intensity;
void main(void) {
// Multiply the mvp matrix by the vertex to obtain our final vertex position
    	gl_Position = mvpmatrix * vec4(in_Position, 1.0);
    
	ex_Color = material1.diffuse * light1.diffuse + 0.005 * in_Color;
    	//ex_Color = in_Color;
	ex_Normal = in_Normal;
	ex_intensity = dot(normalize(vec3(light1.position)), in_Normal);
}
