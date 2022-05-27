#ifndef GLRENDER_H
#define GLRENDER_H
#include <QtGui/QOpenGLFunctions>
#include <QQuickItem>
#include <QtQuick/qquickwindow.h>
#include "header.h"
#include <QDebug>
#include "model.h"
#include "camera.h"
#include "shader.h"
enum{
    PBR_SHADER=0,
    PHONG_SHADER,
    BLINN_PHONG_SHADER,
    NUM_OF_SHADER

};
class GLRender : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLRender();
    inline void setViewportSize(const QSize &size) {
        m_viewportSize = size;
    }

    inline void setWindow(QQuickWindow *window) {
      m_window = window;
      windowFlag = true;
    }


    void render();
    QSize getWindowSize();
    void init();
    void meshBuild();
    void setTouch(float x,float y);
    void setShader(int index);
public slots:
    void paint();

private:
    QSize m_viewportSize;
    QQuickWindow *m_window;
    qreal dWidth;
    qreal dHeight;
    bool windowFlag;
    GLuint VertexArrayID;
    GLuint programID;
    GLuint vertexbuffer;
    bool initFlag;
    Model model;
    Shader shader[NUM_OF_SHADER];
    Shader lightShader;
    Model lightmodel;

    Camera camera;
    vector<unsigned int> VBO, EBO;
    vector<unsigned int> VAO;
    vector<Mesh> meshes;
    GLuint attr[NUM_ATTR_LOC];
    GLuint uniform[NUM_UNIFORM_LOC];
    unsigned int cubeVAO;
    unsigned int cubeVBO;
    unsigned int textureID;
    float lastX;
    float lastY;
    bool firstMouse = true;
    float shiness;
    int selectShader;


};

#endif // GLRENDER_H
