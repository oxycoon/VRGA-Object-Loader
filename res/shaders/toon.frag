#version 150

in vec3 ex_Color;
in vec3 ex_Normal;
in float ex_intensity;

out vec4 gl_FragColor;

void main(void) {
	//gl_FragColor = vec4(ex_Color,1.0);

	if(ex_intensity > 0.95)
		gl_FragColor = vec4(ex_Color * 0.9, 1.0);
	else if(ex_intensity > 0.75)
		gl_FragColor = vec4(ex_Color * 0.75, 1.0);
	else if(ex_intensity > 0.5)
		gl_FragColor = vec4(ex_Color * 0.5, 1.0);
	else if(ex_intensity > 0.25)
		gl_FragColor = vec4(ex_Color * 0.25, 1.0);
	else 
		gl_FragColor = vec4(ex_Color * 0.10, 1.0);
}
