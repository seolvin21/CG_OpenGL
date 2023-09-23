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
GLvoid TimerFunction(int value);

int cnt = 0;
int cnt_i = 0;
bool pause;
bool pressA, pressI, pressC, pressO;
typedef struct _rect {
  float x1;  float y1;
  float x2;  float y2;
  float r;  float g;  float b;
  float speed;
  int directX;  int directY;
} rect;
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
  } else
    return false;
}

void Init() 
{
  for (int i = 0; i < 5; ++i) {
    Rect[i] = {NULL};
  }
}

void main(int argc, char** argv)  // 윈도우 출력하고 콜백함수 설정
{
  srand(time(NULL));
  Init();

  //---윈도우 생성하기
  glutInit(&argc, argv);                         // glut 초기화
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // 디스플레이 모드 설정
  glutInitWindowPosition(0, 0);                  // 윈도우의 위치 지정
  glutInitWindowSize(800, 800);                  // 윈도우의 크기 지정
  glutCreateWindow("Example3");  // 윈도우 생성 윈도우 이름

  //---GLEW 초기화하기
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)  // glew 초기화
  {
    std::cerr << "Unable to initialize GLEW" << std::endl;
    exit(EXIT_FAILURE);
  } else
    std::cout << "GLEW Initialized\n";

  glutDisplayFunc(drawScene);  // 출력 콜백함수의 지정
  glutReshapeFunc(Reshape);    // 다시 그리기 콜백함수 지정
  glutKeyboardFunc(Keyboard);  // 키보드 입력 콜백함수 지정
  glutMouseFunc(Mouse);
  glutMainLoop();  // 이벤트 처리 시작
}

GLvoid drawScene()  //--- 콜백 함수: 그리기 콜백 함수
{
  glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
  glClear(GL_COLOR_BUFFER_BIT);  // 설정된 색으로 전체를 칠하기

  for (int i = 0; i < 5; i++) {
    glColor3f(Rect[i].r, Rect[i].g, Rect[i].b);
    glRectf(Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
  }

  glutSwapBuffers();  // 화면에 출력하기
}

GLvoid Reshape(int w, int h)  //--- 콜백 함수: 다시 그리기 콜백 함수
{
  glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'a':
      pressI = false;
      pressA = !pressA;
      break;
    case 'i':
        pressA = false;
        pressI = !pressI;
      break;
    case 'o':
        pressO = !pressO;
        break;
    case 's':
        pause = !pause;
      glutTimerFunc(50, TimerFunction, 1);
      break;
    case 'r':
       pause = true;
       pressA = false;   pressI = false; pressC = false; pressO = false;
      cnt = 0;
    Init();
      break;
    case 'q':
      glutLeaveMainLoop();
      break;
  }

  glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    // 사각형 추가
    if (cnt <= 5) {
      float mx, my;
      convertDeviceXY2OpenglXY(x, y, &mx, &my);

      Rect[cnt] = {mx - 0.05f,
                   my - 0.05f,
                   mx + 0.05f,
                   my + 0.05f,
                   (rand() % 256) / 255.0f,
                   (rand() % 256) / 255.0f,
                   (rand() % 256) / 255.0f,
                    0.01f};
      Rect[cnt].directX = (rand() % 2 == 0) ? 1 : -1;
      Rect[cnt].directY = (rand() % 2 == 0) ? 1 : -1;

      cnt++;
    }
  }
}

GLvoid TimerFunction(int value)
{
    for (int i = 0; i < 5; ++i) {
        //위치 변화
        if (pressA) {
            int direction = 0;
            if (Rect[i].x1 <= -1.0f) direction = 1;
            else if (Rect[i].y1 <= -1.0f) direction = 2;
            else if (Rect[i].x2 >= 1.0f) direction = 3;
            else if (Rect[i].y2 >= 1.0f) direction = 4;

            switch (direction) {
            case 1:
                Rect[i].directX = 1;
                Rect[i].directY = 1;
                break;
            case 2:
                Rect[i].directX = -1;
                Rect[i].directY = 1;
                break;
            case 3:
                Rect[i].directX = -1;
                Rect[i].directY = -1;
                break;
            case 4:
                Rect[i].directX = 1;
                Rect[i].directY = -1;
                break;
            }

            // 사각형의 위치 업데이트
            Rect[i].x1 += Rect[i].directX * Rect[i].speed;
            Rect[i].x2 += Rect[i].directX * Rect[i].speed;
            Rect[i].y1 += Rect[i].directY * Rect[i].speed;
            Rect[i].y2 += Rect[i].directY * Rect[i].speed;
        }

        else if (pressI) {
            Rect[i].directX = 1;
            Rect[i].x1 += Rect[i].directX * Rect[i].speed;
            Rect[i].x2 += Rect[i].directX * Rect[i].speed;

            if (cnt_i <= 200) {
                Rect[i].directY = 1;
                cnt_i++;
            }
            else if (cnt_i >= 200) {
                Rect[i].directY = -1;
                cnt_i--;
            }

            Rect[i].y1 += Rect[i].directY * Rect[i].speed;
            Rect[i].y2 += Rect[i].directY * Rect[i].speed;
        }

        if (pressO) {
            Rect[i].r = (rand() % 256) / 255.0f;
            Rect[i].g = (rand() % 256) / 255.0f;
            Rect[i].b = (rand() % 256) / 255.0f;
        }
    }


    glutPostRedisplay();

    if (!pause) {
        glutTimerFunc(50, TimerFunction, 1);
    }

}