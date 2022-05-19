#include "glrender.h"

#include <iostream>
#include <fstream>
#include <sstream>
GLRender::GLRender()
{
    initializeOpenGLFunctions();
    initFlag=false;
}
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else {
        printf("파일 %s를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까?\n", vertex_file_path);
        getchar();
        return 0;
    }

    //프래그먼트 쉐이더 코드를 파일에서 읽기
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    //버텍스 쉐이더를 컴파일
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    //버텍스 쉐이더를 검사
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    //프래그먼트 쉐이더를 컴파일
    printf("Compiling shader : %s", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    //프래그먼트 쉐이더를 검사
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    //프로그램에 링크
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    //프로그램 검사
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void GLRender::init(){
    loadModel.loadeFile("../groundstone-sphere/source/sphere.fbx");
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    programID = LoadShaders("Shader/vertextShader.vs", "Shader/fragmentShader.fs");
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,1.0f,0.0f,
    };
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}
void GLRender::paint(){
    if(!initFlag){
        init();
        initFlag=true;
    }
    else{
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);


        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,            //0번째 속성. 0이 될 특별한 이유는 없지만 쉐이더의 레이아웃과 반드시 맞춰야함
            3,            //크기(size)
            GL_FLOAT,    //타입(type)
            GL_FALSE,    //정규화(normalized)?
            0,            //다음 요소까지의 간격(stride)
            (void*)0    //배열 버퍼의 오프셋(offset)
        );

        glDrawArrays(GL_TRIANGLES, 0, 3);    //버텍스 0에서 시작해서~ 총 3개의 버텍스로 -> 하나의 삼각형

        glDisableVertexAttribArray(0);
    }

}
