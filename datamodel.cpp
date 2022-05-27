#include "datamodel.h"

DataModel::DataModel()
{
    camera = Camera(glm::vec3(0.0,0.0,3.0));

}
void DataModel::loadModel(string filePath){

    model = Model(filePath);
}
void DataModel::loadShader(){
    shader[PBR_SHADER] = Shader("../Shader/pbrShader.vs","../Shader/pbrShader.fs");
    shader[PHONG_SHADER] = Shader("../Shader/phongShader.vs","../Shader/phongShader.fs");
    shader[LIGHT_SHADER] = Shader("../Shader/lightShader.vs","../Shader/ligthShader.fs");
}
Model DataModel::getModel(){
    return model;
}
Shader DataModel::getShader(int index){
    return shader[index];
}
Camera DataModel::getCamera(){
    return camera;
}
