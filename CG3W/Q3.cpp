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

int cnt = 1;
bool left_button;
typedef struct _rect {
	float x1;
	float y1;
	float x2;
	float y2;
	float r;
	float g;
	float b;
	bool in;
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
	Rect[0] = { -0.1f, -0.1f, 0.1f, 0.1f,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,
	false };
	for (int i = 1; i < 5; ++i) {
		Rect[i] = { NULL };
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

	for (int i = 0; i < 5; i++) {
		glColor3f(Rect[i].r, Rect[i].g, Rect[i].b);
		glRectf(Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
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
	case 'a':
		//�簢�� �߰�
		if (cnt <= 5) {
			int rx = rand() % 800, ry = rand() & 800;
			float rx_c, ry_c;
			convertDeviceXY2OpenglXY(rx, ry, &rx_c, &ry_c);
			
			Rect[cnt] = { rx_c - 0.1f, ry_c - 0.1f, rx_c + 0.1f, ry_c + 0.1f,
				(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,
			false };

			cnt++;
		}
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
	int i;

	if (left_button == true)
	{

		float mx, my;
		convertDeviceXY2OpenglXY(x, y, &mx, &my);

		for (i = 0; i < 5; i++) {
			Rect[i].in = isinRect(mx, my,
				Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
			if (Rect[i].in)
				break;
		}

		float centerX = (Rect[i].x1 + Rect[i].x2) / 2.0f;
		float centerY = (Rect[i].y1 + Rect[i].y2) / 2.0f;

		if (Rect[i].in) {
			// ���콺 �̵��� ���� �߽� ��ġ ����
			centerX = mx;
			centerY = my;

			// ����� �߽� ��ġ�� ������� �簢�� �»��, ���ϴ� ��ǥ ������Ʈ
			Rect[i].x1 = centerX - 0.1f;
			Rect[i].y1 = centerY - 0.1f;
			Rect[i].x2 = centerX + 0.1f;
			Rect[i].y2 = centerY + 0.1f;
		}

		glutPostRedisplay();
	}

}