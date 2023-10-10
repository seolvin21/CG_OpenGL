#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

//--- 아래 5개 함수는 사용자 정의 함수
void make_vertexShaders();
void make_fragmentShaders();
void InitBuffer();
GLuint make_shaderProgram();
GLvoid drawScene();
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);

//--- 필요한 변수 선언
GLint width, height;
GLuint shaderProgramID;  //--- 세이더 프로그램 이름
GLuint vertexShader;     //--- 버텍스 세이더 객체
GLuint fragmentShader;   //--- 프래그먼트 세이더 객체

const GLfloat triShape[3][3] = { //--- 삼각형 위치 값
{ -0.5, -0.5, 0.0 }, { 0.5, -0.5, 0.0 }, { 0.0, 0.5, 0.0} };
const GLfloat colors[3][3] = { //--- 삼각형 꼭지점 색상
{ 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } };
GLuint vao, vbo[2];


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

void Init()
{

}

//--- 메인 함수
void main(int argc, char** argv)  //--- 윈도우 출력하고 콜백함수 설정
{
    width = 500;
    height = 500;
    Init();

    //--- 윈도우 생성하기
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("Example1");

    //--- GLEW 초기화하기
    glewExperimental = GL_TRUE;
    glewInit();

    //--- 세이더 읽어와서 세이더 프로그램 만들기
    make_vertexShaders();    //--- 버텍스 세이더 만들기
    make_fragmentShaders();  //--- 프래그먼트 세이더 만들기
    shaderProgramID = make_shaderProgram();    //--- 세이더 프로그램 만들기
    InitBuffer();

    glutDisplayFunc(drawScene);  //--- 출력 콜백 함수
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);  // 키보드 입력 콜백함수 지정
    glutMouseFunc(Mouse);   

    glutMainLoop();
}


//--- 출력 콜백 함수
GLvoid drawScene()  //--- 콜백 함수: 그리기 콜백 함수
{
    GLfloat rColor, gColor, bColor;
    rColor = gColor = bColor = 1.0;  //--- 배경색을 흰색으로 설정

   
    glClearColor(rColor, gColor, bColor, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //--- 렌더링 파이프라인에 세이더 불러오기
    glUseProgram(shaderProgramID);

    //--- 사용할 VAO 불러오기
    glBindVertexArray(vao);


    //--- 삼각형 그리기
    // shapes 배열에 있는 정점들을 렌더링
    for (int i = 0; i < cnt; i++) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, shapes[i].trishape);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, shapes[i].color);
        glEnableVertexAttribArray(1);

        glDrawArrays(GL_TRIANGLES, 0, shapes[i].verCnt);
    }

    glutSwapBuffers();  // 화면에 출력하기
}

//--- 다시그리기 콜백 함수
GLvoid Reshape(int w, int h)  //--- 콜백 함수: 다시 그리기 콜백 함수
{
    glViewport(0, 0, w, h);
}


void InitBuffer()
{
    glGenVertexArrays(1, &vao); //--- VAO 를 지정하고 할당하기

    glBindVertexArray(vao); //--- VAO를 바인드하기

    glGenBuffers(2, vbo); //--- 2개의 VBO를 지정하고 할당하기

    for (int i = 0; i < 10; i++) {
        // 버텍스 데이터 VBO 초기화
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat) * shapes[i].verCnt, shapes[i].trishape, GL_STATIC_DRAW);

        // 버텍스 색상 VBO 초기화
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat) * shapes[i].verCnt, shapes[i].color, GL_STATIC_DRAW);
    }

    //--- 좌표값을 attribute 인덱스 0번에 명시한다: 버텍스 당 3* float
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //--- attribute 인덱스 0번을 사용가능하게 함
    glEnableVertexAttribArray(0);


    //--- 색상값을 attribute 인덱스 1번에 명시한다: 버텍스 당 3*float
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //--- attribute 인덱스 1번을 사용 가능하게 함.
    glEnableVertexAttribArray(1);
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
            std::cout << "pressed" << std::endl;
            pressL = false;
            pressR = false;
            pressP = false;
        }
        else
            std::cout << "press canceled" << std::endl;
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
        if (cnt <= 10) {
            std::cout << "clicked" << std::endl;
            float mx, my;
            convertDeviceXY2OpenglXY(x, y, &mx, &my);

            if (pressP) {
                cnt++;
            }
            else if (pressT) {
                // 정점을 추가할 수 있는 경우에만 실행
                shapes[cnt].trishape[shapes[cnt].verCnt][0] = mx;
                shapes[cnt].trishape[shapes[cnt].verCnt][1] = my;
                shapes[cnt].trishape[shapes[cnt].verCnt][2] = 0.0;

                // 색상 데이터 초기화
                shapes[cnt].color[shapes[cnt].verCnt][0] = 1.0;
                shapes[cnt].color[shapes[cnt].verCnt][1] = 0.0;
                shapes[cnt].color[shapes[cnt].verCnt][2] = 0.0;

                shapes[cnt].verCnt++;

                // VBO 업데이트
                glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9 * shapes[cnt].verCnt, shapes[cnt].trishape, GL_STATIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9 * shapes[cnt].verCnt, shapes[cnt].color, GL_STATIC_DRAW);
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
    //--- 버텍스 세이더 읽어 저장하고 컴파일 하기


  //--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
    vertexSource = filetobuf("vertex.glsl");
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR : vertex shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

//--- 프래그먼트 세이더 객체 만들기
void make_fragmentShaders() {
    GLchar* fragmentSource;
    //--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
    fragmentSource = filetobuf("fragment.glsl");  // 프래그세이더 읽어오기

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

    if (!result) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
}

//--- 세이더 프로그램 만들고 세이더 객체 링크하기
GLuint make_shaderProgram()
{
    GLuint shaderProgramID;
    shaderProgramID = glCreateProgram();  //--- 세이더 프로그램 만들기

    glAttachShader(shaderProgramID, vertexShader);  //--- 세이더 프로그램에 버텍스 세이더 붙이기

    glAttachShader(shaderProgramID, fragmentShader);  //--- 세이더 프로그램에 프래그먼트 세이더 붙이기
    glLinkProgram(shaderProgramID);  //--- 세이더 프로그램 링크하기

    glDeleteShader(vertexShader);  //--- 세이더 객체를 세이더 프로그램에
                                   //링크했으므로, 세이더 객체 자체는 삭제 가능
    glDeleteShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &result);  // ---세이더가 잘 연결되었는지 체크하기

    if (!result) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, errorLog);
        std::cerr << "ERROR: shader program 연결 실패\n"
            << errorLog << std::endl;
        return false;
    }

    glUseProgram(shaderProgramID);  //--- 만들어진 세이더 프로그램 사용하기
    //--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
    //--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
    //--- 사용하기 직전에 호출할 수 있다.

    return shaderProgramID;
}