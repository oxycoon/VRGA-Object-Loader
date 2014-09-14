#version 150

precision highp float;

in vec3 in_Position;
in vec3 in_Color;
in vec3 in_Normal;

uniform mat4 mvpmatrix;
uniform mat4 mmatrix;
uniform mat4 vmatrix;


out vec4 ex_Color;
out vec3 ex_Normal;
out vec4 ex_ecPos;

void main(void) {
// Multiply the mvp matrix by the vertex to obtain our final vertex position
	vec3 eyeVector = -in_Position;
	ex_Normal = in_Normal;
	ex_Color = vec4(in_Color,1.0);

	ex_ecPos = vmatrix * mmatrix * vec4(in_Position, 1.0);

	gl_Position = mvpmatrix * vec4(in_Position, 1.0);
}

