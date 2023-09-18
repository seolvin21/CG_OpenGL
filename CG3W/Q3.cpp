#include <iostream>
#include <gl/glew.h>// �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

bool left_button;
typedef struct _rect {
	float x1;
	float y1;
	float x2;
	float y2;
	float r;
	float g;
	float b;
}rect;
rect Rect[5];
void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
	int w = 800;
	int h = 800;
	*ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}


bool isinRect(float mx, float my, float x1, float y1, float x2, float y2)
{
	if (mx >= x1 && my >= y1 && mx <= x2 && my <= y2) {
		return true;
	}
	else
		return false;
}

void Init()
{
	Rect[0] = { -0.2f, -0.2f, 0.2f, 0.2f,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
}

void main(int argc, char** argv)		//������ ����ϰ� �ݹ��Լ� ����
{
	srand(time(NULL));
	Init();

	//---������ �����ϱ�
	glutInit(&argc, argv);							// glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// ���÷��� ��� ����
	glutInitWindowPosition(0, 0);					// �������� ��ġ ����
	glutInitWindowSize(800, 800);					// �������� ũ�� ����
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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene()//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(0, 0, 0, 0); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(Rect[0].x1, Rect[0].y1, Rect[0].x2, Rect[0].y2);

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		//�簢�� �߰�
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		left_button = (state == GLUT_DOWN);
}

GLvoid Motion(int x, int y)
{
	if (left_button == true)
	{
		float mx, my;
		convertDeviceXY2OpenglXY(x, y, &mx, &my);

		float centerX = (Rect[0].x1 + Rect[0].x2) / 2.0f;
		float centerY = (Rect[0].y1 + Rect[0].y2) / 2.0f;

		// ���콺 �̵��� ���� �߽� ��ġ ����
		centerX = mx;
		centerY = my;

		// ����� �߽� ��ġ�� ������� �簢�� �»��, ���ϴ� ��ǥ ������Ʈ
		Rect[0].x1 = centerX - (Rect[0].x2 - centerX);
		Rect[0].y1 = centerY - (Rect[0].y2 - centerY);
		Rect[0].x2 = centerX + (Rect[0].x2 - centerX);
		Rect[0].y2 = centerY + (Rect[0].y2 - centerY);
	}

}