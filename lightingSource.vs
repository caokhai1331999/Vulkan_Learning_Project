#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 gl_position;

uniform mat4 Lmodel;
uniform mat4 Lview;
uniform mat4 Lprojection;

void main()
{
	gl_position = Lprojection* Lview* Lmodel* vec4(aPos, 1.0);
}

