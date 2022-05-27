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
    camera = Camera(glm::vec3(0.0,0.0,3.0));
    shader[PBR_SHADER] = Shader("../Shader/pbrShader.vs","../Shader/pbrShader.fs");
    shader[PHONG_SHADER] = Shader("../Shader/pbrShader.vs","../Shader/pbrShader.fs");
    lightShader = Shader("../Shader/lightShader.vs","../Shader/ligthShader.fs");
    model = Model("../Model/rock/scene.gltf");
    lightmodel= Model("../Model/sphere/scene.gltf");

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
        int offset_y = m_window->height()*0.33;
        int viewWidth =m_window->width();
        int viewHeigth = m_window->height()*0.67;
        glViewport(0,offset_y,viewWidth,viewHeigth);
        shader[selectShader].use();
        glm::mat4 projection = glm::perspective(glm::radians(60.f), (float)m_window->width() / (float)m_window->height(), 0.1f, 1000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::vec3 lightPos(0.3f,0.0f,1.6f);
        shader[selectShader].setMat4("projection", projection);
        shader[selectShader].setMat4("view", view);
        shader[selectShader].setVec3("lightPos",lightPos);
        shader[selectShader].setVec3("lightColor",2.0f,2.0f,2.0f);
        shader[selectShader].setVec3("albedo", 0.5f, 0.0f, 0.0f);
        shader[selectShader].setFloat("ao", 1.0f);
        shader[selectShader].setFloat("metallic", (float)1.0);
        shader[selectShader].setFloat("roughness", glm::clamp(0.0f, 0.05f, 1.0f));
        shader[selectShader].setVec3("camPos", camera.Position);
        shader[selectShader].setFloat("shiness",shiness);
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,glm::radians(lastX),glm::vec3(0.0f,1.0f,0.0f));
        model = glm::rotate(model,glm::radians(90.f),glm::vec3(1.0f,0.0f,0.0f));

        model = glm::translate(model, glm::vec3(0.0f,0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
        shader[selectShader].setMat4("model", model);
        shader[selectShader].setVec3("viewPos",camera.Position);
        lastX+=0.3;


        this->model.Draw(shader[selectShader]);

        /*lightShader.use();
        lightShader.setMat4("projection",projection);
        lightShader.setMat4("view",view);
        model = glm::mat4(1.0f);
        model = glm::translate(model,lightPos);
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        lightShader.setMat4("model", model);
        lightmodel.Draw(lightShader);*/

    }
}
void GLRender::setTouch(float x, float y){
    float xpos = static_cast<float>(x);
        float ypos = static_cast<float>(y);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;


}
