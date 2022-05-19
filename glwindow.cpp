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
        glFormat.setVersion(3,2);
        glFormat.setProfile(QSurfaceFormat::CoreProfile);
        /*I'm showing everything for context, but this is the key line*/
        glFormat.setDepthBufferSize(8);
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

        QMetaObject::invokeMethod(this, "setWindowSize", \
                                  Q_ARG(QVariant, window()->size().width()),
                                  Q_ARG(QVariant, window()->size().height()));
        glRender->setWindow(window());
        glRender->setViewportSize(window()->size() * window()->devicePixelRatio());

        connect(window(), &QQuickWindow::beforeRendering, glRender, &GLRender::paint, Qt::DirectConnection);

    }




}
