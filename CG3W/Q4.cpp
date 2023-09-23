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

void main(int argc, char** argv)  // ������ ����ϰ� �ݹ��Լ� ����
{
  srand(time(NULL));
  Init();

  //---������ �����ϱ�
  glutInit(&argc, argv);                         // glut �ʱ�ȭ
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // ���÷��� ��� ����
  glutInitWindowPosition(0, 0);                  // �������� ��ġ ����
  glutInitWindowSize(800, 800);                  // �������� ũ�� ����
  glutCreateWindow("Example3");  // ������ ���� ������ �̸�

  //---GLEW �ʱ�ȭ�ϱ�
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK)  // glew �ʱ�ȭ
  {
    std::cerr << "Unable to initialize GLEW" << std::endl;
    exit(EXIT_FAILURE);
  } else
    std::cout << "GLEW Initialized\n";

  glutDisplayFunc(drawScene);  // ��� �ݹ��Լ��� ����
  glutReshapeFunc(Reshape);    // �ٽ� �׸��� �ݹ��Լ� ����
  glutKeyboardFunc(Keyboard);  // Ű���� �Է� �ݹ��Լ� ����
  glutMouseFunc(Mouse);
  glutMainLoop();  // �̺�Ʈ ó�� ����
}

GLvoid drawScene()  //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
  glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
  glClear(GL_COLOR_BUFFER_BIT);  // ������ ������ ��ü�� ĥ�ϱ�

  for (int i = 0; i < 5; i++) {
    glColor3f(Rect[i].r, Rect[i].g, Rect[i].b);
    glRectf(Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
  }

  glutSwapBuffers();  // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)  //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
    // �簢�� �߰�
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
        //��ġ ��ȭ
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

            // �簢���� ��ġ ������Ʈ
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