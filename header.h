#ifndef HEADER_H
#define HEADER_H
#include <QQuickItem>
#include <QOpenGLWindow>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include "GLES3/gl3.h"
#include "GLES3/gl3ext.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
using namespace std;
enum{
    ATTR_LOC_POSITION,
    ATTR_LOC_TEXCOORD,
    ATTR_LOC_NORMAL,
    ATTR_LOC_TANGENT,
    ATTR_LOC_BITANGENT,
    NUM_ATTR_LOC
};
enum{
    UNIFORM_LOC_MODEL,
    UNIFORM_LOC_PROJECTION,
    UNIFORM_LOC_VIEW,
    NUM_UNIFORM_LOC
};
#define AUTO_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE NAME() const { return a_ ## NAME ; } \
       void NAME(TYPE value); \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE a_ ## NAME;


#endif // HEADER_H
