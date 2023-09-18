#include <iostream>
#include <gl/glew.h>// 필요한 헤더파일 include
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

void main(int argc, char** argv)		//윈도우 출력하고 콜백함수 설정
{
	srand(time(NULL));
	Init();

	//---윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(800, 800);					// 윈도우의 크기 지정
	glutCreateWindow("Example1");					// 윈도우 생성 윈도우 이름

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
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();					// 이벤트 처리 시작
}

GLvoid drawScene()//--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(0, 0, 0, 0); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(Rect[0].x1, Rect[0].y1, Rect[0].x2, Rect[0].y2);

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		//사각형 추가
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

		// 마우스 이동에 따라 중심 위치 변경
		centerX = mx;
		centerY = my;

		// 변경된 중심 위치를 기반으로 사각형 좌상단, 우하단 좌표 업데이트
		Rect[0].x1 = centerX - (Rect[0].x2 - centerX);
		Rect[0].y1 = centerY - (Rect[0].y2 - centerY);
		Rect[0].x2 = centerX + (Rect[0].x2 - centerX);
		Rect[0].y2 = centerY + (Rect[0].y2 - centerY);
	}

}