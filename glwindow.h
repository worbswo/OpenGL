#ifndef GLWINDOW_H
#define GLWINDOW_H
#include "header.h"
#include "glrender.h"
#include <QTouchEvent>


class GLWindow : public QQuickItem
{
    Q_OBJECT
    AUTO_PROPERTY(qreal,gw)
public:
    GLWindow();
    Q_INVOKABLE void setShader(int index);
    Q_INVOKABLE void setShiness(float value);
    Q_INVOKABLE void setModelScale(float value);
    Q_INVOKABLE void setLightPositionZ(float value);
    Q_INVOKABLE void setLightPositionXY(float valueX,float valueY);
public slots:
    void sync();
    void release();



private slots:
    void handleWindowChanged(QQuickWindow *win);
private:
    GLRender *glRender;

};

#endif // GLWINDOW_H
