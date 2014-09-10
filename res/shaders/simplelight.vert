#version 150

precision highp float;

in vec3 in_Position;
in vec3 in_Color;
in vec3 in_Normal;

// mvpmatrix is the result of multiplying the model, view, and projection matrices */
uniform mat4 mvpmatrix;
uniform vec3 lightDirection;

out vec3 ex_Color;
out vec3 ex_Normal;
void main(void) {
    	
    



    	ex_Color = in_Color;
	ex_Normal = in_Normal;

	gl_Position = mvpmatrix * vec4(in_Position, 1.0);
}
