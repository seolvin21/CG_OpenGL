#pragma once
#include "header.h"
#include "header_user.h"
#include "Model.h"

class CContext
{
private:
	CShader* m_program;
	//std::vector<CMesh*>m_meshes;
	CMesh* m_box;
	CMesh* m_tetra;

	int tree_count = 10;

	// object
	float m_obj_radian_x{ 0.0f };
	float m_obj_radian_y{ 0.0f };
	float m_tree_ry{ 45.0f };

	// camera parameter
	bool m_camera_control{ false };
	
	// cmera rotate
	float m_camera_y{ 0.0f }; // y축


	// camera front 방향 결정 각도
	float m_camera_pitch{ -10.0f }; // x축
	float m_camera_yaw{ 0.0f }; // y축
	// roll 대신 up vector로 컨트롤

	//glm::vec3 m_camera_pos{ glm::vec3(0.0f, 5.0f, 5.0f) };
	glm::vec3 m_camera_front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 m_camera_up{ glm::vec3(0.0f, 1.0f, 0.0f) };
	glm::vec2 m_prev_pos{ glm::vec2(0.0f, 0.0f) };

	// light
	glm::vec3 radius = { glm::vec3(0.0f, 7.0f, 0.0f) };

	//glm::vec3 m_light_pos{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 m_light_color{ glm::vec3(1.0f, 1.0f, 1.0f) };
	glm::vec3 m_object_color{ glm::vec3(0.8f, 0.8f, 0.8f) };
	float m_ambient_strength{ 0.1f };
	float m_spec_strength{ 0.6f };
	float m_spec_shininess{ 32.0f };

	// 객체 변환 변수
	float m_light_obj_y{ 0.0f };
	std::vector<std::vector<float>> cube_color;

public:
	CContext();
	~CContext();
public:
	void Init();
	void KeyBoard(const unsigned char& key, const int& x, const int& y);
	void Mouse(const int& button, const int& state, const int& x, const int& y);
	void Motion(const int& x, const int& y);
	void Time(int value);
	void Render();
	void Update();
};

