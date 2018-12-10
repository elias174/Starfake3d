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
    glm::mat4 *c_matrix_model;
    glm::vec3 current_position;
    glm::vec3 current_scale;


    Arwing() {
        this->shader = new Shader("1.model_loading.vs", "1.model_loading.fs");
        this->model = new Model(FileSystem::getPath("resources/objects/Arwing/Arwing.obj"));

        //original_position
        current_position = glm::vec3(0.0f, -19.75f, 0.0f);
        current_scale = glm::vec3(0.1f, 0.1f, 0.1f);
    }

    void pre_draw(glm::mat4 *projection, glm::mat4 *view){
        this->projection = projection;
        this->view = view;
        this->shader->setMat4("projection", *this->projection);
        this->shader->setMat4("view", *this->view);

        glm::mat4 matrix_model;
        matrix_model = glm::translate(matrix_model, this->current_position); // translate it down so it's at the center of the scene
        matrix_model = glm::scale(matrix_model, this->current_scale);	// it's a bit too big for our scene, so scale it down
        this->shader->setMat4("model", matrix_model);
    }

    void draw(){
        this->model->Draw(*this->shader);
    }

    void move(int move){
        if(move == (int) GLFW_KEY_W)
            this->current_position.y += 2.0f;
        else if(move == (int) GLFW_KEY_S)
            this->current_position.y -= 2.0f;
        else if(move == (int) GLFW_KEY_A)
            this->current_position.x -= 2.0f;
        else if(move == (int) GLFW_KEY_D)
            this->current_position.x += 2.0f;
    }
};


#endif // ARWING_H
