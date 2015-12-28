#version 150 core

uniform vec3 uColor;

in vec3 passNormal;

out vec4 outColor;

void main()
{
	vec3 lightDir = vec3(1,1,-1);
	normalize(lightDir);
	float diffuseIntensity = dot(passNormal, lightDir);
	diffuseIntensity = max(diffuseIntensity, 0.2);
	
	outColor = vec4(uColor * diffuseIntensity, 1);
}