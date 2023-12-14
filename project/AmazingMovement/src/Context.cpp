#include "Context.h"

CContext::CContext()
{

}

CContext::~CContext()
{
    if (m_program) {
        delete m_program;
    }
    /*for (auto& mesh : m_meshes) {
        delete mesh;
    }*/
    if (m_box) {
        delete m_box;
    }
}

void CContext::KeyBoard(const unsigned char& key, const int& x, const int& y)
{
    const float camera_speed = 0.05f;

    // 카메라 x축은 카메라 UP벡터와 z축 벡터의 직교를 단위 벡터로 만든 것이다.
    auto camera_right = glm::normalize(glm::cross(m_camera_up, -m_camera_front));
    auto camera_up = glm::normalize(glm::cross(-m_camera_front, camera_right));
    switch (key) {
    case 'r':
        break;
    case 'q':
        exit(0);
    default:
        break;
    }

    glutPostRedisplay();
}

void CContext::Mouse(const int& button, const int& state, const int& x, const int& y)
{
}

void CContext::Motion(const int& x, const int& y)
{
}

void CContext::Render()
{
    glm::vec3 camera_pos(0.0f, 7.0f, 20.0f);
    auto camera_trans = glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_y), glm::vec3(0.0f, 1.0f, 0.0f));
    camera_pos = camera_trans * glm::vec4(camera_pos, 1.0f);

    m_camera_front = glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_yaw), glm::vec3(0.0f, 1.0f, 0.0f)) * 
        glm::rotate(glm::mat4(1.0f), glm::radians(m_camera_pitch), glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

    auto projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.01f, 50.0f);

    auto view = glm::lookAt(
        camera_pos,
        camera_pos + m_camera_front,
        m_camera_up);

    // 조명 위치 계산
    glm::vec3 light_pos(0.0f, 0.0f, 0.0f);
    auto light_trans = glm::rotate(glm::mat4(1.0f), glm::radians(m_light_obj_y), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0), radius);
    light_pos = light_trans * glm::vec4(light_pos, 1.0f);

    m_program->UseShader();
    
    // 모델 조명
    m_program->SetUniform("viewPos", camera_pos);
    m_program->SetUniform("lightPos", light_pos);
    m_program->SetUniform("ambientStrength", m_ambient_strength);
    m_program->SetUniform("specularStrength", m_spec_strength);
    m_program->SetUniform("specularShininess", m_spec_shininess);
    m_program->SetUniform("objectColor", m_object_color);

    m_program->SetUniform("lightColor", m_light_color);
   
    // 바닥
    m_program->SetUniform("objectColor", glm::vec3(0.8f, 0.1f, 0.1f));
    auto model = glm::translate(glm::mat4(1.0), glm::vec3(0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(5.0f, 0.3f, 50.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    auto transform = projection * view * model;
    // transform, model 변환 행렬 전달
    m_program->SetUniform("transform", transform);
    m_program->SetUniform("modelTransform", model);
    m_program->SetUniform("invModelTransform", transpose(inverse(model)));

    m_box->Draw(m_program);

    // 큐브
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            m_program->SetUniform("objectColor", glm::vec3(cube_color[i][j]));
            model = glm::translate(glm::mat4(1.0), glm::vec3(-1.2f + 1.2f * j, 1.0f + 1.2f * i, 10.0f))
                * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_y), glm::vec3(0.0f, 1.0f, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
                * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
 
            transform = projection * view * model;
            // transform, model 변환 행렬 전달
            m_program->SetUniform("transform", transform);
            m_program->SetUniform("modelTransform", model);
            m_program->SetUniform("invModelTransform", transpose(inverse(model)));
    
            m_box->Draw(m_program);
        }
    }

    // 나무
    GLfloat tree_z = -30.0f;
    for (int i = 0; i < tree_count; ++i) {

        tree_z += 6.0f;

        m_program->SetUniform("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(glm::mat4(1.0), glm::vec3(3.8f, 3.0f, tree_z))
            * glm::scale(glm::mat4(1.0f), glm::vec3(2.5f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = projection * view * model;

        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
        m_tetra->Draw(m_program);

        m_program->SetUniform("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(glm::mat4(1.0), glm::vec3(3.8f, 2.4f, tree_z))
            * glm::scale(glm::mat4(1.0f), glm::vec3(2.5f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = projection * view * model;

        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
        m_tetra->Draw(m_program);

        m_program->SetUniform("objectColor", glm::vec3(0.5f, 0.3f, 0.0f));
        model = glm::translate(glm::mat4(1.0), glm::vec3(3.8f, 0.3f, tree_z))
            * glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = projection * view * model;

        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
        m_box->Draw(m_program);
    }

    GLfloat tree_z2 = -30.0f;
    for (int i = 0; i < tree_count; ++i) {
        tree_z2 += 6.0f;

        m_program->SetUniform("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(glm::mat4(1.0), glm::vec3(-3.8f, 3.0f, tree_z2))
            * glm::scale(glm::mat4(1.0f), glm::vec3(2.5f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = projection * view * model;

        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
        m_tetra->Draw(m_program);

        m_program->SetUniform("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(glm::mat4(1.0), glm::vec3(-3.8f, 2.4f, tree_z2))
            * glm::scale(glm::mat4(1.0f), glm::vec3(2.5f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = projection * view * model;

        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
        m_tetra->Draw(m_program);

        m_program->SetUniform("objectColor", glm::vec3(0.5f, 0.3f, 0.0f));
        model = glm::translate(glm::mat4(1.0), glm::vec3(-3.8f, 0.3f, tree_z2))
            * glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
            * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = projection * view * model;

        m_program->SetUniform("transform", transform);
        m_program->SetUniform("modelTransform", model);
        m_program->SetUniform("invModelTransform", transpose(inverse(model)));
        m_box->Draw(m_program);
    }


    // 산
    m_program->SetUniform("objectColor", glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(glm::mat4(1.0), glm::vec3(-3.8f, 3.0f, tree_z2))
        * glm::scale(glm::mat4(1.0f), glm::vec3(2.5f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_tree_ry), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(m_obj_radian_x), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    transform = projection * view * model;

    m_program->SetUniform("transform", transform);
    m_program->SetUniform("modelTransform", model);
    m_program->SetUniform("invModelTransform", transpose(inverse(model)));
    m_tetra->Draw(m_program);
}

void CContext::Init()
{
	m_program = new CShader("vertex.glsl", "fragment.glsl");
	m_program->MakeShaderProgram();

    m_box = new CMesh();
    m_box->CreateBox();

    m_tetra = new CMesh();
    m_tetra->CreateSquarePy();

    // 큐브 색깔 초기화
    cube_color.resize(3);
    for (int i = 0; i < 3; ++i) {
        cube_color[i].resize(3);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cube_color[i][j] = 0.8f;
        }
    }
}

void CContext::Update()
{
}

void CContext::Time(int value)
{
    if (value == 1) {
        
        glutPostRedisplay();
    }
}
