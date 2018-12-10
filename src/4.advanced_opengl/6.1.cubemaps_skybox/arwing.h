#ifndef ARWING_H
#define ARWING_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <iostream>


class Arwing
{
public:
    Shader *shader;
    Model *model;
    glm::mat4 *projection;
    glm::mat4 *view;


    Arwing() {
        this->shader = new Shader("1.model_loading.vs", "1.model_loading.fs");
        this->model = new Model(FileSystem::getPath("resources/objects/Arwing/Arwing.obj"));
    }

    void draw(glm::mat4 *projection, glm::mat4 *view){
        glm::mat4 matrix_model;
        this->projection = projection;
        this->view = view;
        matrix_model = glm::translate(matrix_model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        matrix_model = glm::scale(matrix_model, glm::vec3(0.5f, 0.5f, 0.5f));	// it's a bit too big for our scene, so scale it down
        this->shader->setMat4("model", matrix_model);
        this->shader->setMat4("view", *this->view);
        this->shader->setMat4("projection", *this->projection);
        this->model->Draw(*this->shader);
    }
};


#endif // ARWING_H
