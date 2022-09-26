#version 330 core
layout (location = 0) in vec4 inPos;
layout (location = 1) in vec2 inTexture;

out vec2 outTexture;

// NOTE(__LUNA__): Macos doesn't like mat4
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(inPos.x, -inPos.yz, inPos.w);
	outTexture = inTexture;
}
