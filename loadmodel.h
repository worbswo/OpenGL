#ifndef LOADMODEL_H
#define LOADMODEL_H
#include "assimp/Importer.hpp"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <string>
#include "header.h"
using namespace std;

class LoadModel
{
public:
    LoadModel();
    Assimp::Importer impoter;
    const aiScene *pScene;
    void loadeFile(string filePath);
    Mesh processMesh(aiMesh *aimesh,const aiScene *scene);
    void processNode(aiNode *node, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int TextureFromFile(const char *path, const string &directory);
    vector<Mesh> meshes;
    vector<Texture>textures_loaded;
    string directory;
    vector<Mesh> getMesh();

};

#endif // LOADMODEL_H
