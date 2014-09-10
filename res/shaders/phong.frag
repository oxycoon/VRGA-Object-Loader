#version 150

in vec3 ex_Color;
in vec3 ex_Normal;

out vec4 gl_FragColor;

uniform vec3 lightDirection;

void main(void) {
	//gl_FragColor = vec4(ex_Color,1.0);

	vec3 lightVector = lightDirection;
	vec3 diffuseMaterial = ex_Color;
	vec3 specularMaterial = vec3(0.4, 0.4, 0.4);

	vec3 normalVector = normalize(ex_Normal);

	vec3 eyeVector = vec3(0.0, 0.0, 1.0);
	vec3 halfVector = normalize(lightVector + eyeVector);

	vec3 diffuse = vec3(max(0.5*dot(normalVector, lightVector), 0.5)) * diffuseMaterial;

	vec3 specular = vec3(max(dot(normalVector, halfVector), 0.0));
	specular = pow(specular.x, 32) * specularMaterial;

	//gl_FragColor = vec4(ex_Color,1.0);
	gl_FragColor = vec4(diffuse+specular, 1.0);
}
