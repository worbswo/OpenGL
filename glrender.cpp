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
}


void GLRender::init(){
    camera = Camera(glm::vec3(0.0,0.0,3.0));
    shader = Shader("../Shader/vertextShader.vs","../Shader/fragmentShader.fs");
    model = Model("../sphere/source/sphere.obj");
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


        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(80.f), (float)m_window->width() / (float)m_window->height(), 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model,glm::radians(lastX),glm::vec3(0.0f,1.0f,0.0f));
        model = glm::translate(model, glm::vec3(0.0f,0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader.setMat4("model", model);
        lastX+=0.5;


        this->model.Draw(shader);


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
