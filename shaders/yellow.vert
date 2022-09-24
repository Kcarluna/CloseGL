#version 330 core
layout (location = 0) in vec4 pos;

out vec4 position;

uniform float translate;

void main()
{
	gl_Position = vec4(translate - pos.x, pos.yzw);
	position = pos;
}
