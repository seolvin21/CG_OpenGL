#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;

uniform mat4 transform;
uniform mat4 modelTransform;
uniform mat4 invModelTransform;	// ��ȯ�� ���� ���

out vec3 out_Normal;
out vec3 out_Position; // ��ǻ�� ���� ���� ��ǥ�迡�� �����ؾ���

void main(void) 
{
	gl_Position = transform * vec4 (in_Position, 1.0f);
	out_Normal = (invModelTransform * vec4(in_Normal, 0.0f)).xyz;
	out_Position = (modelTransform * vec4(in_Position, 1.0f)).xyz;
}