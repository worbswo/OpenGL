#ifndef HEADER_H
#define HEADER_H
#include <QQuickItem>
#include <QOpenGLWindow>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>

#define AUTO_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE NAME() const { return a_ ## NAME ; } \
       void NAME(TYPE value); \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE a_ ## NAME;
#endif // HEADER_H
