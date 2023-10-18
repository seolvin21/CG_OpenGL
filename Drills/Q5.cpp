#include <iostream>
#include <gl/glew.h>// 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);

float size = 0.0f;
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
rect Rect[20];
rect eraser;

void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
	int w = 800;
	int h = 800;
	*ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
	*oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}


bool isinRect(float ex1, float ey1, float ex2, float ey2, float x1, float y1, float x2, float y2)
{
	if (ex1 < x2 && ex2 > x1 && ey1 < y2 && ey2 > y1) {
		if (x1 == NULL) {
			return false;
		}
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
			(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,
		false};
	}
}

void main(int argc, char** argv)		//윈도우 출력하고 콜백함수 설정
{
	srand(time(NULL));
	Init();

	//---윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(800, 800);					// 윈도우의 크기 지정
	glutCreateWindow("Example3");					// 윈도우 생성 윈도우 이름

	//---GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)					// glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glutDisplayFunc(drawScene);		// 출력 콜백함수의 지정
	glutReshapeFunc(Reshape);		// 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();					// 이벤트 처리 시작
}

GLvoid drawScene()//--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	for (int i = 0; i < 20; i++) {
		glColor3f(Rect[i].r, Rect[i].g, Rect[i].b);
		glRectf(Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
	}

	if (left_button) {
		glColor3f(eraser.r, eraser.g, eraser.b);
		glRectf(eraser.x1, eraser.y1, eraser.x2, eraser.y2);
	}

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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
			eraser.r = 0;
			eraser.g = 0;
			eraser.b = 0;
			size = 0.0f;
		}
	}
}

GLvoid Motion(int x, int y)
{
	int i;

	if (left_button == true)
	{
		//지우개 움직임
		float mx, my;
		convertDeviceXY2OpenglXY(x, y, &mx, &my);

		float centerX = (eraser.x1 + eraser.x2) / 2.0f;
		float centerY = (eraser.y1 + eraser.y2) / 2.0f;

		centerX = mx;
		centerY = my;

		eraser.x1 = centerX - 0.05f - size;
		eraser.y1 = centerY - 0.05f - size;
		eraser.x2 = centerX + 0.05f + size;
		eraser.y2 = centerY + 0.05f + size;


		//배경 사각형 충돌
		for (i = 0; i < 20; i++) {
			Rect[i].in = isinRect(eraser.x1, eraser.y1, eraser.x2, eraser.y2,
				Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);

			if (Rect[i].in) {
				std::cout << "Collision" << std::endl;

				eraser.r = Rect[i].r;
				eraser.g = Rect[i].g;
				eraser.b = Rect[i].b;
				size += 0.01f;
				Rect[i] = { NULL };
			}
		}
		glutPostRedisplay();
	}
}