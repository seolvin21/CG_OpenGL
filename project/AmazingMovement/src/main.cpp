#include "Context.h"

CContext context;

using std::cout;
using std::endl;
void PrintKey()
{
	cout << "o : 색깔 초기화" << endl;
	cout << "p : 프로그램 종료" << endl;
}

void DrawScene()
{
	glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	context.Update();
	context.Render();
	glutSwapBuffers();
}

void KeyBoard(unsigned char key, int x, int y)
{
	context.KeyBoard(key, x, y);
}

void Mouse(int button, int state, int x, int y)
{
	context.Mouse(button, state, x, y);
}

void Motion(int x, int y)
{
	context.Motion(x, y);
}

void Time(int value)
{
	context.Time(value);
	glutTimerFunc(context.GetSpeed(), Time, 1);
}

int main(int argc, char** argv)
{

	PlaySound(TEXT(SOUND_FILE_BGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);

	CGL::GetInstance()->InitWindow(argc, argv, WIDTH, HEIGHT, "Amazing Movement");
	CGL::GetInstance()->Render(DrawScene);

	context.Init();
	// 깊이 검사 설정
	glEnable(GL_DEPTH_TEST);
	

	PrintKey();

	glutKeyboardFunc(KeyBoard);
	//glutMouseFunc(Mouse);
	//glutMotionFunc(Motion);
	glutTimerFunc(100, Time, 1);
	glutMainLoop();

	// 깊이 
	glDisable(GL_DEPTH_TEST);
}

