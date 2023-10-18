#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#define TYPE

//--- �Ʒ� 5�� �Լ��� ����� ���� �Լ�
void make_vertexShaders();
void make_fragmentShaders();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);

//--- �ʿ��� ���� ����
GLint width, height;
GLuint shaderProgramID;  //--- ���̴� ���α׷� �̸�
GLuint vertexShader;     //--- ���ؽ� ���̴� ��ü
GLuint fragmentShader;   //--- �����׸�Ʈ ���̴� ��ü

typedef struct _shape {
    GLfloat vertices[30];
    int verCnt;
    GLfloat color[3];
}Shape;
Shape shapes[10];

int cnt = 0;
bool pressP = false, pressL = false, pressT = false, pressR = false;


void convertDeviceXY2OpenglXY(int x, int y, float* ox, float* oy)
{
    int w = 800;
    int h = 800;
    *ox = (float)((x - (float)w / 2.0) * (float)(1.0 / (float)(w / 2.0)));
    *oy = -(float)((y - (float)h / 2.0) * (float)(1.0 / (float)(h / 2.0)));
}

char* filetobuf(const char* file) 
{
    FILE* fptr;
    long length;
    char* buf;

    fptr = fopen(file, "rb");  // Open file for reading
    if (!fptr)                 // Return NULL on failure
      return NULL;

    fseek(fptr, 0, SEEK_END);  // Seek to the end of the file

    length = ftell(fptr);      // Find out how many bytes into the file we are

    buf = (char*)malloc(length + 1);  // Allocate a buffer for the entire length
                                        // of the file and a null terminator

    fseek(fptr, 0, SEEK_SET);         // Go back to the beginning of the file
    fread(buf, length, 1, fptr);      // Read the contents of the file in to the buffer
    fclose(fptr);     // Close the file

    buf[length] = 0;  // Null terminator

    return buf;       // Return the buffer
}


//--- ���� �Լ�
void main(int argc, char** argv)  //--- ������ ����ϰ� �ݹ��Լ� ����
{
  width = 500;
  height = 500;

  //--- ������ �����ϱ�
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(width, height);
  glutCreateWindow("Example1");

  //--- GLEW �ʱ�ȭ�ϱ�
  glewExperimental = GL_TRUE;
  glewInit();

  //--- ���̴� �о�ͼ� ���̴� ���α׷� �����
  make_vertexShaders();    //--- ���ؽ� ���̴� �����
  make_fragmentShaders();  //--- �����׸�Ʈ ���̴� �����
  shaderProgramID = make_shaderProgram();    //--- ���̴� ���α׷� �����

  glutDisplayFunc(drawScene);  //--- ��� �ݹ� �Լ�
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);  // Ű���� �Է� �ݹ��Լ� ����


  glutMainLoop();
}


//--- ��� �ݹ� �Լ�
GLvoid drawScene()  //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
  GLfloat rColor, gColor, bColor;
  rColor = gColor = 0.0;
  bColor = 1.0;  //--- ������ �Ķ������� ����

  glClearColor(rColor, gColor, bColor, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgramID);

  for (int i = 0; i < cnt; i++) {
      Shape shape = shapes[i];
      
      glPointSize(5.0);
      glDrawArrays(GL_POINTS, 0, 1);  //--- �������ϱ�: 0�� �ε������� 1���� ���ؽ��� ����Ͽ� �� �׸���
  }
  glutSwapBuffers();  // ȭ�鿡 ����ϱ�
}

//--- �ٽñ׸��� �ݹ� �Լ�
GLvoid Reshape(int w, int h)  //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
  glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'p':
        pressP = !pressP;
        if (pressP) {
            pressL = false;
            pressR = false;
            pressT = false;
        }
        break;
    case 'l':
        pressL = !pressL;
        if (pressL) {
            pressP = false;
            pressR = false;
            pressT = false;
        }
        break;
    case 't':
        pressT = !pressT;
        if (pressT) {
            pressL = false;
            pressR = false;
            pressP = false;
        }
        break;
    case 'r':
        pressR = !pressR;
        if (pressR) {
            pressP = false;
            pressL = false;
            pressT = false;
        }
        break;
    case 'c':
        break;
    case 'q':
        glutLeaveMainLoop();
        break;
    }

    glutPostRedisplay();
}

GLvoid Mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (cnt <= 9) {
            float mx, my;
            convertDeviceXY2OpenglXY(x, y, &mx, &my);

            if (pressP) {
                cnt++;
            }
            else if (pressT) {
                cnt++;
            }
            else if (pressR) {
                cnt++;
            }
            else if (pressL) {
                cnt++;
            }
            
        }
    }
}


void make_vertexShaders() 
{
    GLchar* vertexSource;
      //--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�


    //--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
    vertexSource = filetobuf("vertex.glsl");
    vertexShader = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource (vertexShader, 1, &vertexSource, NULL);
    glCompileShader (vertexShader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv (vertexShader, GL_COMPILE_STATUS, &result);

    if(!result) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR : vertex shader ������ ����\n" << errorLog<< std::endl;
        return;
    }
}

//--- �����׸�Ʈ ���̴� ��ü �����
void make_fragmentShaders() {
    GLchar* fragmentSource;
    //--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
    fragmentSource = filetobuf("fragment.glsl");  // �����׼��̴� �о����

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
        return;
    }
}

//--- ���̴� ���α׷� ����� ���̴� ��ü ��ũ�ϱ�
GLuint make_shaderProgram() 
{
    GLuint shaderProgramID;
    shaderProgramID = glCreateProgram();  //--- ���̴� ���α׷� �����

    glAttachShader(shaderProgramID, vertexShader);  //--- ���̴� ���α׷��� ���ؽ� ���̴� ���̱�

    glAttachShader(shaderProgramID, fragmentShader);  //--- ���̴� ���α׷��� �����׸�Ʈ ���̴� ���̱�
    glLinkProgram(shaderProgramID);  //--- ���̴� ���α׷� ��ũ�ϱ�

    glDeleteShader(vertexShader);  //--- ���̴� ��ü�� ���̴� ���α׷���
                                   //��ũ�����Ƿ�, ���̴� ��ü ��ü�� ���� ����
    glDeleteShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);  // ---���̴��� �� ����Ǿ����� üũ�ϱ�

    if (!result) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
        std::cerr << "ERROR: shader program ���� ����\n"
                  << errorLog << std::endl;
        return false;
    }

    glUseProgram(shaderProgramID);  //--- ������� ���̴� ���α׷� ����ϱ�
    //--- ���� ���� ���̴����α׷� ���� �� �ְ�, �� �� �Ѱ��� ���α׷��� ����Ϸ���
    //--- glUseProgram �Լ��� ȣ���Ͽ� ��� �� Ư�� ���α׷��� �����Ѵ�.
    //--- ����ϱ� ������ ȣ���� �� �ִ�.

    return shaderProgramID;
}