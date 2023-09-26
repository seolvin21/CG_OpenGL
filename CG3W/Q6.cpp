#include <iostream>
#include <gl/glew.h>// 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <stdlib.h>
#include <time.h>
#define RECT_SIZE 0.3f
GLvoid Reshape(int w, int h);
GLvoid drawScene(GLvoid);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid TimerFunction(int value);

bool pause = false;
typedef struct _rect {
    float x1;  float y1;
    float x2;  float y2;
    float r;  float g;  float b;
    bool clicked;
} rect;
rect Rect[5];
rect Splits[4];

void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
    int w = 800;
    int h = 800;
    *ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
    *oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

bool isinRect(float mx, float my, float x1, float y1, float x2, float y2)
{
    if (mx > x1 && my > y1 && mx < x2 && my < y2) {
        return true;
    }
    else
        return false;
}

void Init()
{
    int x, y;
    float cx, cy;
    for (int i = 0; i < 5; ++i) {
        x = (rand() % 700 + 1);	y = (rand() % 700 + 1);
        convertDeviceXY2OpenglXY(x, y, &cx, &cy);
        Rect[i] = { cx, cy, cx + 0.3f, cy + 0.3f,
            (rand() % 256) / 255.0f,(rand() % 256) / 255.0f,(rand() % 256) / 255.0f,
        false };
    }
    for (int i = 0; i < 4; ++i) {
        Splits[i] = { NULL };
    }
}

void SplitRect(int index)
{
    float midX = (Rect[index].x1 + Rect[index].x2) / 2.0f;
    float midY = (Rect[index].y1 + Rect[index].y2) / 2.0f;

    Splits[0] = { midX - (RECT_SIZE / 2),midY,midX,midY + (RECT_SIZE / 2),
        Rect[index].r,Rect[index].g ,Rect[index].b };      //좌상단
    Splits[1] = { midX,midY,midX + (RECT_SIZE / 2),midY + (RECT_SIZE / 2),
        Rect[index].r,Rect[index].g ,Rect[index].b };      //우상단
    Splits[2] = { midX - (RECT_SIZE / 2),midY - (RECT_SIZE / 2),midX,midY,
        Rect[index].r,Rect[index].g ,Rect[index].b };      //좌하단
    Splits[3] = { midX,midY - (RECT_SIZE / 2),midX + (RECT_SIZE / 2),midY,
        Rect[index].r,Rect[index].g ,Rect[index].b };      //우하단

    Rect[index] = { NULL };
}

void main(int argc, char** argv)  // 윈도우 출력하고 콜백함수 설정
{
    srand(time(NULL));
    Init();

    //---윈도우 생성하기
    glutInit(&argc, argv);                         // glut 초기화
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // 디스플레이 모드 설정
    glutInitWindowPosition(800, 400);                  // 윈도우의 위치 지정
    glutInitWindowSize(800, 800);                  // 윈도우의 크기 지정
    glutCreateWindow("Example3");  // 윈도우 생성 윈도우 이름

    //---GLEW 초기화하기
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)  // glew 초기화
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
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

    for (int i = 0; i < 4; i++) {
        glColor3f(Splits[i].r, Splits[i].g, Splits[i].b);
        glRectf(Splits[i].x1, Splits[i].y1, Splits[i].x2, Splits[i].y2);
    }

    glutSwapBuffers();  // 화면에 출력하기
}

GLvoid Reshape(int w, int h)  //--- 콜백 함수: 다시 그리기 콜백 함수
{
    glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'q':
        glutLeaveMainLoop();
        break;
    }
    glutPostRedisplay();
}

int clickedRectIndex = -1;
GLvoid Mouse(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float mx, my;
        convertDeviceXY2OpenglXY(x, y, &mx, &my);
        for (int i = 0; i < 5; ++i) {
            Rect[i].clicked = isinRect(mx, my, Rect[i].x1, Rect[i].y1, Rect[i].x2, Rect[i].y2);
            if (Rect[i].clicked) {
                std::cout << "Rect" << i << " clicked" << std::endl;
                clickedRectIndex = i;
                SplitRect(i);
                glutTimerFunc(100, TimerFunction, 1);
                break;
            }
        }
    }
}

GLvoid TimerFunction(int value)
{
    for (int i = 0; i < 4; i++) {
        // Splits 배열에 대한 업데이트 수행
        if (clickedRectIndex != -1) {
            clickedRectIndex = i;
            std::cout << "-" << i << std::endl;

            // 사각형을 작아지는 방향으로 업데이트
            Splits[i].x1 += 0.005f;
            Splits[i].y1 += 0.005f;
            Splits[i].x2 -= 0.005f;
            Splits[i].y2 -= 0.005f;

            Splits[i].x1 -= 0.01f;
            Splits[i].x2 -= 0.01f;

            // 일정 크기 이하로 작아지면 사라지도록 처리
            if (Splits[i].x1 >= Splits[i].x2 || Splits[i].y1 >= Splits[i].y2) {
                Splits[i] = { NULL };
                clickedRectIndex = -1;
            }
        }
    }

    glutPostRedisplay();

    if (!pause && clickedRectIndex != -1) {
        glutTimerFunc(100, TimerFunction, 1);
    }

}