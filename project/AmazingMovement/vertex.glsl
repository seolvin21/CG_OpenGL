#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;

uniform mat4 transform;
uniform mat4 modelTransform;
uniform mat4 invModelTransform;	// 변환에 의해 노멀

out vec3 out_Normal;
out vec3 out_Position; // 디퓨즈 값은 월드 좌표계에서 적용해야함

void main(void) 
{
	gl_Position = transform * vec4 (in_Position, 1.0f);
	out_Normal = (invModelTransform * vec4(in_Normal, 0.0f)).xyz;
	out_Position = (modelTransform * vec4(in_Position, 1.0f)).xyz;
}