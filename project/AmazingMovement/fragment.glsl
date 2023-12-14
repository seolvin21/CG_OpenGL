#version 330 core

in vec3 out_Normal; 
in vec3 out_Position;
out vec4 FragColor; //--- 색상 출력

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
	vec3 pixelNorm = normalize(out_Normal);	// 픽셀로 선형보간할 때 단위벡터가 아닐 수 있음
	vec3 diffuse = max(dot(pixelNorm, lightDir), 0.0) * lightColor;	// 90 이상은 볼 필요 없음

	vec3 viewDir = normalize(viewPos - out_Position);
	vec3 reflectDir = reflect(-lightDir, pixelNorm); // 입사각의 반전
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), specularShininess); // specularShininess 값이 클 수록 하이라이트의 면적이 좁아짐
	vec3 specular = specularStrength * spec * lightColor;

	vec3 result = (ambient + diffuse + specular) * objectColor;
	FragColor = vec4 (result, 0.5);
}