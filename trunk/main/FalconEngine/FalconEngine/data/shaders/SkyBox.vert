#version 150 core

uniform mat4 WorldViewProjectionMatrix;

in vec3 inPosition;
out vec3 passTexCoord;

void main()
{
	gl_Position =  WorldViewProjectionMatrix * vec4(inPosition,1);
	
	// use local vertex position as cubemap lookup vector
	passTexCoord = inPosition;
}