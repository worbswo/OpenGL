#include "glrender.h"

#include <iostream>
#include <fstream>
#include <sstream>
GLRender::GLRender()
{
    initializeOpenGLFunctions();
    initFlag=false;
    lastX=0;
    lastY=0;
    shiness=32;
    selectShader = PBR_SHADER;
}


void GLRender::init(){
    dataModel.loadModel("../Model/rock/scene.gltf");
    dataModel.loadShader();

    camera = dataModel.getCamera();
    shader = dataModel.getShader(PBR_SHADER);
    model = dataModel.getModel();

}
void GLRender::paint(){
    if(!initFlag){
        init();
        initFlag=true;
    }
    else{
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_CULL_FACE);
        glEnable(GL_MULTISAMPLE);

        glClearColor(0.109f, 0.109f, 0.117f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        int offset_y  = m_window->height()*0.33;
        int viewWidth = m_window->width();
        int viewHeigth= m_window->height()*0.67;
        glViewport(0,offset_y,viewWidth,viewHeigth);
        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(60.f), (float)m_window->width() / (float)m_window->height(), 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::vec3 lightPos(0.3f,0.0f,1.6f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setVec3("lightPos",lightPos);
        shader.setVec3("lightColor",1.0f,1.0f,1.0f);
        shader.setVec3("albedo", 0.5f, 0.0f, 0.0f);
        shader.setFloat("ao", 1.0f);
        shader.setFloat("metallic", (float)1.0);
        shader.setFloat("roughness", glm::clamp(0.0f, 0.05f, 1.0f));
        shader.setVec3("camPos", camera.Position);
        shader.setFloat("shiness",shiness);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,glm::radians(lastX),glm::vec3(0.0f,1.0f,0.0f));
        model = glm::rotate(model,glm::radians(90.f),glm::vec3(1.0f,0.0f,0.0f));

        model = glm::translate(model, glm::vec3(0.0f,0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
        shader.setMat4("model", model);
        shader.setVec3("viewPos",camera.Position);
        lastX+=0.3;

        this->model.Draw(shader);

    }
}
void GLRender::setShader(int index){
    shader = dataModel.getShader(index);
}
