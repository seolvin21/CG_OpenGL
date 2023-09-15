#include <iostream>
#include <gl/glew.h>// 필요한 헤더파일 include
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

void main(int argc, char** argv)		//윈도우 출력하고 콜백함수 설정
{
	srand(time(NULL));

	//---윈도우 생성하기
	glutInit(&argc, argv);							// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);	// 디스플레이 모드 설정
	glutInitWindowPosition(0, 0);					// 윈도우의 위치 지정
	glutInitWindowSize(800, 600);					// 윈도우의 크기 지정
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
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	glutMainLoop();					// 이벤트 처리 시작
}

GLvoid drawScene()//--- 콜백 함수: 그리기 콜백 함수
{
	glClearColor(r,g,b,1.0f); // 바탕색을 ‘blue’ 로 지정
	glClear(GL_COLOR_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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