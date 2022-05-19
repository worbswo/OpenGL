#ifndef GLRENDER_H
#define GLRENDER_H
#include <QtGui/QOpenGLFunctions>
#include <QQuickItem>
#include <QtQuick/qquickwindow.h>
#include "header.h"
#include <QDebug>
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
};

#endif // GLRENDER_H
