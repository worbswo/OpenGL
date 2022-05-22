QT += qml quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        camera.cpp \
        glrender.cpp \
        glwindow.cpp \
        main.cpp \
        mesh.cpp \
        model.cpp \
        shader.cpp \
        stb_image.c

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
LIBS+= -lassimp -lglfw
HEADERS += \
    camera.h \
    glrender.h \
    glwindow.h \
    header.h \
    mesh.h \
    model.h \
    shader.h \
    stb_image.h
