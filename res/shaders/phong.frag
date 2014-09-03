
varying vec3 Normal;

void main () 
{

    vec3 lightVec = vec3(gl_LightSource[0].position);
    vec3 diffuseMaterial = gl_FrontLightProduct[0].diffuse.xyz;
    vec3 specularMaterial = gl_FrontLightProduct[0].specular.xyz;
	
    vec3 NormalVec = normalize(Normal);
    // calculate half angle vector
    vec3 eyeVec = vec3(0.0, 0.0, 1.0);
    vec3 halfVec = normalize(lightVec + eyeVec);

    // calculate diffuse component
    vec3 diffuse = vec3(max(0.5*dot(NormalVec, lightVec), 0.5)) * diffuseMaterial;

    // calculate specular component
    vec3 specular = vec3(max(dot(NormalVec, halfVec), 0.0));
    specular = pow(specular.x, 32.0) * specularMaterial;

    // combine diffuse and specular contributions and output final vertex color
    gl_FragColor.rgb = diffuse + specular;
}