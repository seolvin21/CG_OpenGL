#include <iostream>
#include <gl/glew.h>// �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid TimerFunction(int value);

float r = 0, g = 0, b = 0;
bool pressT = false;

void main(int argc, char** argv)		//������ ����ϰ� �ݹ��Լ� ����
{
	srand(time(NULL));

	//---������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);					// �������� ��ġ ����
	glutInitWindowSize(800, 600);					// �������� ũ�� ����
	glutCreateWindow("Example1");					// ������ ���� ������ �̸�

	//---GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)					// glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene);		// ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape);		// �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����
	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene()//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(r,g,b,1.0f); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	// �׸��� �κ� ����: �׸��� ���� �κ��� ���⿡ ���Եȴ�.

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid TimerFunction(int value)
{
	r = (rand() % 256) / 255.0f;
	g = (rand() % 256) / 255.0f;
	b = (rand() % 256) / 255.0f;

	glutPostRedisplay();

	if (pressT) {
		glutTimerFunc(1000, TimerFunction, 1);
	}
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		r = 0;
		g = 1.0f;
		b = 1.0f;
		break;

	case 'm':
		r = 1.0f;
		g = 0;
		b = 1.0f;
		break;

	case 'y':
		r = 1.0f;
		g = 1.0f;
		b = 0;
		break;

	case 'a':
		r = (rand() % 256) / 255.0f;
		g = (rand() % 256) / 255.0f;
		b = (rand() % 256) / 255.0f;
		break;

	case 'w':
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		break;

	case 'k':
		r = 0.0f;
		g = 0.0f;
		b = 0.0f;
		break;

	case 't':
		pressT = true;
		glutTimerFunc(1000, TimerFunction, 1);

		break;
	case 's':
		pressT = false;
		break;
	case 'q':
		glutLeaveMainLoop();
		break;
	}

	glutPostRedisplay();
}