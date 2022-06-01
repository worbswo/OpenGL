#include "glwindow.h"
#include <unistd.h>

GLWindow::GLWindow()
{
   connect(this, &QQuickItem::windowChanged, this, &GLWindow::handleWindowChanged);

}
void GLWindow::gw(qreal gw)
{

    emit gwChanged(gw);
    if (window()){
        window()->update();
    }

}
void GLWindow::handleWindowChanged(QQuickWindow *win)
{
    qDebug("handleWindowChanged");
    if (win) {
        /// emmitted before the scene graph is synchronized
        connect(win, &QQuickWindow::beforeSynchronizing, this, &GLWindow::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated, this, &GLWindow::release, Qt::DirectConnection);
        win->setClearBeforeRendering(false);
        QSurfaceFormat glFormat;
        /*I'm showing everything for context, but this is the key line*/
        glFormat.setDepthBufferSize(24);
        glFormat.setAlphaBufferSize(8);
        glFormat.setRedBufferSize(8);
        glFormat.setGreenBufferSize(8);
        glFormat.setBlueBufferSize(8);
        glFormat.setSamples(8);
        win->setFormat(glFormat);

    }
}
void GLWindow::release()
{
    if (glRender) {
        delete glRender;
        glRender = 0;
    }
}

void GLWindow::sync()
{
    if (!glRender) {

        glRender = new GLRender();

        /// paint glRender before the scene starts rendering


        glRender->setWindow(window());
        glRender->setViewportSize(window()->size() * window()->devicePixelRatio());

        connect(window(), &QQuickWindow::beforeRendering, glRender, &GLRender::paint, Qt::DirectConnection);

    }




}


void GLWindow::setShader(int index){
    glRender->setShader(index);
}
void GLWindow::setShiness(float value){
    if (glRender) {
        glRender->setShiness(value);
    }
}
void GLWindow::setModelScale(float value){
    if(glRender){
        glRender->setModelScale(value);
    }
}
void GLWindow::setLightPositionZ(float value){
    if(glRender){
        glRender->setLightPositionZ(value);
    }
}

void GLWindow::setLightPositionXY(float valueX, float valueY){
    if(glRender){
        glRender->setLightPositionXY(valueX,valueY);
    }
}
