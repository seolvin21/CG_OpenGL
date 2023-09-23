#include <iostream>
#include <gl/glew.h>// �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Keyboard(unsigned char key, int x, int y);
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
rect Rect[20];
rect eraser;

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
	int x, y;
	float cx, cy;
	for (int i = 0; i < 20; ++i) {
		x = (rand() % 790 + 1);	y = (rand() % 790 + 1);
		convertDeviceXY2OpenglXY(x, y, &cx, &cy);
		Rect[i] = { cx, cy, cx + 0.05f, cy + 0.05f,
			(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f};
	}
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
	glutCreateWindow("Example3");					// ������ ���� ������ �̸�

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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene()//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	for (int i = 0; i < 20; i++) {
		glColor3f(Rect[i].r, Rect[i].g, Rect[i].b);
		glRectf(Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
	}

	if (left_button) {
		glColor3f(0,0,0);
		glRectf(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
	}

	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'r':
		Init();
		break;
	}

	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			left_button = true;
		}
		else if (state == GLUT_UP) {
			left_button = false;
		}
	}
}

GLvoid Motion(int x, int y)
{
	if (left_button == true)
	{
		//���찳 ������
		float mx, my;
		convertDeviceXY2OpenglXY(x, y, &mx, &my);

		float centerX = (eraser.x1 + eraser.x2) / 2.0f;
		float centerY = (eraser.y1 + eraser.y2) / 2.0f;

		centerX = mx;
		centerY = my;

		eraser.x1 = centerX - 0.05f;
		eraser.y1 = centerY - 0.05f;
		eraser.x2 = centerX + 0.05f;
		eraser.y2 = centerY + 0.05f;


		//��� �簢�� �浹

		glutPostRedisplay();
	}
}