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
#include "datamodel.h"
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
    }


    void render();
    QSize getWindowSize();
    void init();
    void meshBuild();
    void setTouch(float x,float y);
    void setShader(int index);
    void setShiness(float value);
    void setModelScale(float value);
    void setLightPositionZ(float value);
    void setLightPositionXY(float valueX,float valueY);
public slots:
    void paint();

private:
    QSize m_viewportSize;
    QQuickWindow *m_window;
    qreal dWidth;
    qreal dHeight;
    DataModel dataModel;
    bool initFlag;
    Model model;
    Shader shader;
    Camera camera;
    float lastX;
    float lastY;
    float shiness;
    int selectShader;
    float modelScale;
    glm::vec3 lightPos;


};

#endif // GLRENDER_H
