#version 430

layout (location=0) in vec3 position;
layout (location=1) in vec3 in_color;

uniform mat4 m_matrix;
uniform mat4 proj_matrix;
uniform mat4 color_matrix;

out vec4 out_color;

void main(void) {
	gl_Position = proj_matrix * m_matrix * vec4(position, 1.0);
	out_color = color_matrix * vec4(in_color, 1.0);
} 
