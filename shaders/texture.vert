#version 330 core
layout (location = 0) in vec4 inPos;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexture;

out vec4 outColor;
out vec2 outTexture;

# NOTE(__LUNA__): Macos does not like mat4 uniforms.....
uniform mat4 transform;

void main()
{
	gl_Position = transform * inPos;
	outColor = inColor;
	outTexture = inTexture;
}
