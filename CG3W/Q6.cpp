#include <iostream>
#include <gl/glew.h>// �ʿ��� ������� include
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
        Rect[index].r,Rect[index].g ,Rect[index].b };      //�»��
    Splits[1] = { midX,midY,midX + (RECT_SIZE / 2),midY + (RECT_SIZE / 2),
        Rect[index].r,Rect[index].g ,Rect[index].b };      //����
    Splits[2] = { midX - (RECT_SIZE / 2),midY - (RECT_SIZE / 2),midX,midY,
        Rect[index].r,Rect[index].g ,Rect[index].b };      //���ϴ�
    Splits[3] = { midX,midY - (RECT_SIZE / 2),midX + (RECT_SIZE / 2),midY,
        Rect[index].r,Rect[index].g ,Rect[index].b };      //���ϴ�

    Rect[index] = { NULL };
}

void main(int argc, char** argv)  // ������ ����ϰ� �ݹ��Լ� ����
{
    srand(time(NULL));
    Init();

    //---������ �����ϱ�
    glutInit(&argc, argv);                         // glut �ʱ�ȭ
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);  // ���÷��� ��� ����
    glutInitWindowPosition(800, 400);                  // �������� ��ġ ����
    glutInitWindowSize(800, 800);                  // �������� ũ�� ����
    glutCreateWindow("Example3");  // ������ ���� ������ �̸�

    //---GLEW �ʱ�ȭ�ϱ�
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)  // glew �ʱ�ȭ
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
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

    for (int i = 0; i < 4; i++) {
        glColor3f(Splits[i].r, Splits[i].g, Splits[i].b);
        glRectf(Splits[i].x1, Splits[i].y1, Splits[i].x2, Splits[i].y2);
    }

    glutSwapBuffers();  // ȭ�鿡 ����ϱ�
}

GLvoid Reshape(int w, int h)  //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
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
        // Splits �迭�� ���� ������Ʈ ����
        if (clickedRectIndex != -1) {
            clickedRectIndex = i;
            std::cout << "-" << i << std::endl;

            // �簢���� �۾����� �������� ������Ʈ
            Splits[i].x1 += 0.005f;
            Splits[i].y1 += 0.005f;
            Splits[i].x2 -= 0.005f;
            Splits[i].y2 -= 0.005f;

            Splits[i].x1 -= 0.01f;
            Splits[i].x2 -= 0.01f;

            // ���� ũ�� ���Ϸ� �۾����� ��������� ó��
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