#include <iostream>
#include <gl/glew.h>// �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Mouse(int button, int state, int x, int y);

typedef struct _rect {
	float x1;
	float y1;
	float x2;
	float y2;
	bool in;
	float r;
	float g;
	float b;
}rect;

rect Rects[4];
rect BRects[4];
float r = 0, g = 0, b = 0;

void InitRect()
{
	Rects[0] = { -1.0f, 0, 0, 1.0f,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
	Rects[1] = { 0, 0, 1.0f, 1.0f,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
	Rects[2] = { -1.0f, -1.0f, 0, 0,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
	Rects[3] = { 0, -1.0f, 1.0f, 0,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };

	BRects[0] = { -1.0f, 0, 0, 1.0f,false,
	(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
	BRects[1] = { 0, 0, 1.0f, 1.0f,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
	BRects[2] = { -1.0f, -1.0f, 0, 0,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
	BRects[3] = { 0, -1.0f, 1.0f, 0,false,
		(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f };
}

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


void main(int argc, char** argv)		//������ ����ϰ� �ݹ��Լ� ����
{
	srand(time(NULL));
	InitRect();

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
	glutMainLoop();					// �̺�Ʈ ó�� ����
}

GLvoid drawScene()//--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	glClearColor(r, g, b, 0); // �������� ��blue�� �� ����
	glClear(GL_COLOR_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	//���
	glColor3f(BRects[0].r, BRects[0].g, BRects[0].b);
	glRectf(BRects[0].x1, BRects[0].y1, BRects[0].x2, BRects[0].y2);

	glColor3f(BRects[1].r, BRects[1].g, BRects[1].b);
	glRectf(BRects[1].x1, BRects[1].y1, BRects[1].x2, BRects[1].y2);

	glColor3f(BRects[2].r, BRects[2].g, BRects[2].b);
	glRectf(BRects[2].x1, BRects[2].y1, BRects[2].x2, BRects[2].y2);

	glColor3f(BRects[3].r, BRects[3].g, BRects[3].b);
	glRectf(BRects[3].x1, BRects[3].y1, BRects[3].x2, BRects[3].y2);


	//�簢��
	glColor3f(Rects[0].r, Rects[0].g, Rects[0].b);
	glRectf(Rects[0].x1, Rects[0].y1, Rects[0].x2, Rects[0].y2);

	glColor3f(Rects[1].r, Rects[1].g, Rects[1].b);
	glRectf(Rects[1].x1, Rects[1].y1, Rects[1].x2, Rects[1].y2);

	glColor3f(Rects[2].r, Rects[2].g, Rects[2].b);
	glRectf(Rects[2].x1, Rects[2].y1, Rects[2].x2, Rects[2].y2);

	glColor3f(Rects[3].r, Rects[3].g, Rects[3].b);
	glRectf(Rects[3].x1, Rects[3].y1, Rects[3].x2, Rects[3].y2);
	
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}

GLvoid Mouse(int button, int state, int x, int y)
{
	float insideRect;
	float mx, my;
	int i = 0;

	// ���콺 ��Ŭ�� �̺�Ʈ�� �߻��� ���
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// ������ ��ǥ�� OpenGL ��ǥ�� ��ȯ
		convertDeviceXY2OpenglXY(x, y, &mx, &my);

		for (i = 0; i < 4; ++i) {
			Rects[i].in = isinRect(mx, my,
				Rects[i].x1, Rects[i].y1, Rects[i].x2, Rects[i].y2);
			BRects[i].in = isinRect(mx, my,
				BRects[i].x1, BRects[i].y1, BRects[i].x2, BRects[i].y2);
			if (Rects[i].in || BRects[i].in) {
				break;
			}
		}

		if (Rects[i].in) {
			std::cout << "inside" << std::endl;
			Rects[i].r = (rand() % 256) / 255.0f;
			Rects[i].g = (rand() % 256) / 255.0f;
			Rects[i].b = (rand() % 256) / 255.0f;

		}
		else {
			std::cout << "outside" << std::endl;
			BRects[i].r = (rand() % 256) / 255.0f;
			BRects[i].g = (rand() % 256) / 255.0f;
			BRects[i].b = (rand() % 256) / 255.0f;
		}

	}

	// ���콺 ��Ŭ�� �̺�Ʈ�� �߻��� ���
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		convertDeviceXY2OpenglXY(x, y, &mx, &my);

		for (i = 0; i < 4; ++i) {
			Rects[i].in = isinRect(mx, my,
				Rects[i].x1, Rects[i].y1, Rects[i].x2, Rects[i].y2);
			BRects[i].in = isinRect(mx, my,
				BRects[i].x1, BRects[i].y1, BRects[i].x2, BRects[i].y2);
			if (Rects[i].in || BRects[i].in) {
				break;
			}
		}

		if (Rects[i].in) {
			std::cout << "inside" << std::endl;
			Rects[i].x1 += 0.2f;
			Rects[i].y1 += 0.2f;
			Rects[i].x2 -= 0.2f;
			Rects[i].y2 -= 0.2f;
		}
		else {
			Rects[i].x1 -= 0.2f;
			Rects[i].y1 -= 0.2f;
			Rects[i].x2 += 0.2f;
			Rects[i].y2 += 0.2f;
		}

	}
}