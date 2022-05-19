#ifndef GLWINDOW_H
#define GLWINDOW_H
#include "header.h"
#include "glrender.h"
class GLWindow : public QQuickItem
{
    Q_OBJECT
    AUTO_PROPERTY(qreal,gw)
public:
    GLWindow();
public slots:
    void sync();
    void release();

private slots:
    void handleWindowChanged(QQuickWindow *win);
private:
    GLRender *glRender;

};

#endif // GLWINDOW_H
