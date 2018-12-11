#ifndef BULLET_H
#define BULLET_H

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


class Bullet
{
public:
    Shader *shader;
    Model *model;
    glm::mat4 *projection;
    glm::mat4 *view;
    glm::mat4 *c_matrix_model;
    glm::vec3 current_position;
    glm::vec3 current_scale;

    Bullet(glm::vec3 current_position) {
        this->shader = new Shader("1.model_loading.vs", "1.model_loading.fs");
        this->model = new Model(FileSystem::getPath("resources/objects/projectile/bazooka_projectile.obj"));

        //original_position
        this->current_position = current_position;
        this->current_position.z += 13.0f;
//        this->current_position.z += 3.0f;

        current_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    void pre_draw(glm::mat4 *projection, glm::mat4 *view){
        this->projection = projection;
        this->view = view;
        this->shader->setMat4("projection", *this->projection);
        this->shader->setMat4("view", *this->view);

        glm::mat4 matrix_model;

        matrix_model = glm::translate(matrix_model, this->current_position); // translate it down so it's at the center of the scene
        matrix_model = glm::scale(matrix_model, this->current_scale);	// it's a bit too big for our scene, so scale it down

        matrix_model = glm::rotate(matrix_model, -3.14f/2.0f, glm::vec3(0.0f, 0.5f, 0.0f));
        this->shader->setMat4("model", matrix_model);
    }

    glm::vec3 get_center_collide(){
        return  this->current_position;
    }

    GLfloat get_radio_collide(){
        GLfloat radio = 6.0f;
        return radio;
    }

    void draw(){
        this->model->Draw(*this->shader);
    }

    void move(){
        this->current_position.z += 3.0f*0.16f;
    }

};

#endif // BULLET_H
