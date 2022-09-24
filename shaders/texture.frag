#version 330 core
out vec4 FragColor;

in vec4 outColor;
in vec2 outTexture;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixture;

void main()
{
	FragColor = mix(texture(texture1, outTexture), texture(texture2, vec2(1.0 - outTexture.x, outTexture.y)), mixture);
}
