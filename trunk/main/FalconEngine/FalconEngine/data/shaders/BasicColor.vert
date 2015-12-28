#version 150 core

uniform mat4 WorldMatrix;
uniform mat4 WorldViewProjectionMatrix;


in vec3 inPosition;
in vec3 inNormal;

out vec3 passNormal;

void main()
{
	gl_Position =  WorldViewProjectionMatrix * vec4(inPosition,1);
	
	passNormal = (WorldMatrix * vec4(inNormal, 0)).xyz;
}