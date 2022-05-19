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
#include "stb_image.h"
using namespace std;
#define AUTO_PROPERTY(TYPE, NAME) \
    Q_PROPERTY(TYPE NAME READ NAME WRITE NAME NOTIFY NAME ## Changed ) \
    public: \
       TYPE NAME() const { return a_ ## NAME ; } \
       void NAME(TYPE value); \
       Q_SIGNAL void NAME ## Changed(TYPE value);\
    private: \
       TYPE a_ ## NAME;

struct Vertex{
 glm::vec3 position;
 glm::vec3 normal;
 glm::vec2 texcoords;
 glm::vec3 tangent;
 glm::vec3 biTangent;
};
struct Texture{
    unsigned int id;
    string type;
    string path;
};

struct Mesh{
    vector<Vertex> verties;
    vector<Texture> textures;
    vector<unsigned int>     indcies;
};
#endif // HEADER_H
