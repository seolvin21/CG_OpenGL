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
	float m_camera_y{ 0.0f }; // y��


	// camera front ���� ���� ����
	float m_camera_pitch{ -15.0f }; // x��
	float m_camera_yaw{ 0.0f }; // y��
	// roll ��� up vector�� ��Ʈ��

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

	// ��ü ��ȯ ����
	float m_light_obj_y{ 0.0f };
	int cube_speed{ 100 };

	// �÷��̾� ť��
	std::vector<std::vector<glm::vec3>> player_color;
	int color_cnt[3][3]; // �÷��̾ �ʿ�
	float player_z{ 11.0f };

	// ���� ť��
	std::vector<std::vector<glm::vec3>> cube_color; // ������ϴ� ť��
	float cube_z{-20.0f};
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

	// ������ �Լ�
	void GenCube();
	bool CheckColor();
	int GetSpeed() { return cube_speed; }
};

