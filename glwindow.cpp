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
void GLWindow::touchEvent(QTouchEvent *event)
{
  float radius,pitch,head;
  int id = event->type();
  float disX;
  float disY;
  float currX[4],currY[4];
  float tmpX[4],tmpY[4];

  int cnt = 0;
  foreach(QTouchEvent::TouchPoint n,event->touchPoints()){
      tmpX[cnt] =n.pos().x();
      tmpY[cnt] =n.pos().y();

        glRender->setTouch(n.pos().x(),n.pos().y());
    currX[cnt] = n.pos().x();
    currY[cnt] = n.pos().y();

    cnt ++;
  }
    qDebug()<<"sss";
}

void GLWindow::setShader(int index){
    glRender->setShader(index);
}
