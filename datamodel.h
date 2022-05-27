#ifndef DATAMODEL_H
#define DATAMODEL_H

#include "model.h"
#include "camera.h"
#include "shader.h"
#include "header.h"
class DataModel
{
public:
    DataModel();
    void loadModel(string filePath);
    void loadShader();
    Shader getShader(int index);
    Model getModel();
    Camera getCamera();

private:
    Shader shader[NUM_OF_SHADER];
    Model  model;
    Camera camera;
};

#endif // DATAMODEL_H
