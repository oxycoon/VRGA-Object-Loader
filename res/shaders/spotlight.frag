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


in vec4 ex_Color;
in vec3 ex_Normal;
in vec4 ex_ecPos;

uniform Light light1;
uniform Material material1;

out vec4 gl_FragColor;

void main(void) {
	vec3 n, halfV, viewV, lightDir, spotDir;
	float NdotL, NdotSL, NdotHV;
	vec3 ambient, specular, diffuse;
	float att, lightDist, spotEffect;

	Light spotlight = Light(
		vec3(0.2, 0.6, 0.3),
		vec3(0.7, 0.2, 0.6),
		vec3(0.4, 0.4, 0.4),
		vec3(10.0, 10.0, 10.0),
		normalize(normalize(light1.eyePosition) - normalize(vec3(10.0, 10.0, 10.0))),
		vec3(-10.0, -10.0, -10.0),
		light1.eyePosition,
		0.15,
		0.40,
		0.50,
		light1.constantAttenuation,
		light1.linearAttenuation,
		light1.quadraticAttenuation);

	lightDir = vec3(light1.position - vec3(ex_ecPos));
	lightDist = length(light1.position);

	spotDir = vec3(spotlight.position - vec3(ex_ecPos));

	ambient = light1.ambient * material1.ambient;
	specular = light1.specular * material1.specular;
	diffuse = light1.diffuse * material1.diffuse;
	
	vec4 color = vec4(ambient, 1.0) + 0.0001*ex_Color;//ex_color is a hack

	n = normalize(ex_Normal);
	halfV = normalize(light1.eyePosition) - normalize(light1.position);

	NdotL = max(dot(n,normalize(lightDir)),0.0);
	NdotSL = max(dot(n,normalize(spotDir)), 0.0);

	if(NdotSL > 0.0)
	{
		spotEffect = dot(normalize(spotlight.spotDirection), 
				normalize(-spotDir));
		if(spotEffect > spotlight.spotCosCutoff)
		{
			spotEffect = pow(spotEffect, spotlight.spotExponent);
			att = spotEffect / (spotlight.constantAttenuation + spotlight.linearAttenuation * lightDist +
				spotlight.quadraticAttenuation * lightDist * lightDist);
			color += att * vec4(diffuse * NdotSL + ambient, 1.0);

			NdotHV = max(dot(n,halfV),0.0);
			color += att * vec4(specular * pow(NdotHV, material1.shininess), 1.0);
		}
	}

	/*if(NdotL > 0.0)
	{
		att = 1 / (light1.constantAttenuation + light1.linearAttenuation * lightDist +
				light1.quadraticAttenuation * lightDist * lightDist);
		color += vec4(att * (diffuse * NdotL + ambient), 1.0);

		NdotHV = max(dot(n,halfV),0.0);
		color += att * vec4(specular,1.0) * pow(NdotHV, material1.shininess);		
	}*/


	gl_FragColor = color;
}
