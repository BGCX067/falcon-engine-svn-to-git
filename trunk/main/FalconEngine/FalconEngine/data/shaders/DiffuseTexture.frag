#version 150 core

uniform sampler2D uDiffuseTextureSampler;

in vec2 passTexCoord;
in vec3 passNormal;

out vec4 outColor;

void main()
{
	vec3 lightDir = vec3(1,1,1);
	lightDir = normalize(lightDir);
	
	float diffuseIntensity = dot(normalize(passNormal), lightDir);
	diffuseIntensity = max(diffuseIntensity, 0.2);
	
	vec3 sampledColor = (texture2D(uDiffuseTextureSampler, passTexCoord)).xyz;
	outColor = vec4(sampledColor * (diffuseIntensity), 1);
}