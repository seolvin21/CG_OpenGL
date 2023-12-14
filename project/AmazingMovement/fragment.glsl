#version 330 core

in vec3 out_Normal; 
in vec3 out_Position;
out vec4 FragColor; //--- ���� ���

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform float specularShininess;
uniform vec3 viewPos;

void main(void) 
{
	vec3 ambient = ambientStrength * lightColor;

	vec3 lightDir = normalize(lightPos - out_Position);
	vec3 pixelNorm = normalize(out_Normal);	// �ȼ��� ���������� �� �������Ͱ� �ƴ� �� ����
	vec3 diffuse = max(dot(pixelNorm, lightDir), 0.0) * lightColor;	// 90 �̻��� �� �ʿ� ����

	vec3 viewDir = normalize(viewPos - out_Position);
	vec3 reflectDir = reflect(-lightDir, pixelNorm); // �Ի簢�� ����
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularShininess); // specularShininess ���� Ŭ ���� ���̶���Ʈ�� ������ ������
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4 (result, 0.5);
}