#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/QQuickView>
#include <QSurfaceFormat>
#include "glwindow.h"


int main(int argc, char *argv[])
{
   QGuiApplication app(argc, argv);

   qmlRegisterType<GLWindow>("OpenGLUnderQML", 1, 0, "GLWindow");
   QSurfaceFormat format;
   QVector<QQuickView *> views;
       for (QScreen *screen : app.screens()) {
           QQuickView *view = new QQuickView;
           view->setTitle("SVM");
           view->setScreen(screen);
           view->setResizeMode(QQuickView::SizeRootObjectToView);
           view->setSource(QUrl("qrc:/main.qml"));
           QObject::connect(view->engine(), &QQmlEngine::quit, qGuiApp, &QCoreApplication::quit);
           format.setSamples(16);
           format.setDepthBufferSize(24);
           format.setStencilBufferSize(24);

           view->setFormat(format);
           views.append(view);
           view->show();
       }
       int result = app.exec();


   qDeleteAll(views);
   return result;
}
