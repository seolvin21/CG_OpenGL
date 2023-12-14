#include "GL.h"
#include "header.h"


void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

CGL::CGL()
{
	// initWindow���� ����
}

CGL::~CGL()
{

}

void CGL::InitWindow(int argc, char** argv, const int& x, const int& y, std::string_view name)
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(x, y);
	glutCreateWindow(name.data());


	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "glew �ʱ�ȭ ����" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "glew �ʱ�ȭ ���� " << std::endl;
}


void CGL::Render(void (*funcptr)(void))
{
	::glutDisplayFunc(funcptr);
	::glutReshapeFunc(Reshape);

}


glm::vec2  CGL::ConvertPoint(const int& x, const int& y)
{
	glm::vec2 tmp;
	tmp.x = (double)((x - (double)WIDTH / 2.0) * (double)(1.0 / (double)(WIDTH / 2.0)));
	tmp.y = -(double)((y - (double)HEIGHT / 2.0) * (double)(1.0 / (double)(HEIGHT / 2.0)));

	return tmp;
}