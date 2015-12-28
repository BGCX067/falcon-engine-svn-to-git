#version 150 core

uniform sampler2D uDiffuseTextureSampler;

in vec2 passTexCoord;
in vec3 passNormal;

out vec4 outColor;

void main()
{	
	vec3 sampledColor = (texture2D(uDiffuseTextureSampler, passTexCoord)).xyz;

	//Ignore black texels
	if (sampledColor.rgb == vec3(0.0, 0.0, 0.0)) {
		discard;
	}

	outColor = vec4(sampledColor, 1);
}