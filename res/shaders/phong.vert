#version 150

precision highp float;

in vec3 in_Normal;
in vec3 in_Color;
in vec3 in_Position

uniform mat4 mvpmatrix;

out vec3 ex_Color;
out vec3 ex_Normal;
void main()
{
    //Normal = gl_NormalMatrix * gl_Normal;
    //gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_FrontColor = gl_Color;

	gl_Position = mvpmatrix * vec4(in_Position, 1.0);
	ex_Color = in_Color;
	ex_Normal = in_Normal;
}