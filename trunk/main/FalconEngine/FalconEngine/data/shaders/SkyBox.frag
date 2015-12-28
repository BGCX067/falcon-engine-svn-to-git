#version 150 core

uniform samplerCube uSkyBoxSampler;

in vec3 passTexCoord;
out vec4 outColor;

void main()
{
	outColor = texture(uSkyBoxSampler, passTexCoord);
}