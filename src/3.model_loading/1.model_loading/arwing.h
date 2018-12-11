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
#include <vector>
#include "bullet.h"


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
    vector<Bullet> bullets;


    Arwing() {
        this->shader = new Shader("1.model_loading.vs", "1.model_loading.fs");
        this->model = new Model(FileSystem::getPath("resources/objects/Arwing/Arwing.obj"));
        //this->model = new Model(FileSystem::getPath("resources/objects/asteroid/10464_Asteroid_v1_Iterations-2.obj"));

        //original_position
        current_position = glm::vec3(0.0f, -19.75f, 0.0f);
        current_scale = glm::vec3(0.1f, 0.1f, 0.1f);
//        current_scale = glm::vec3(0.005f, 0.005f, 0.005f);

    }

    void pre_draw(glm::mat4 *projection, glm::mat4 *view){
        this->projection = projection;
        this->view = view;
        this->shader->setMat4("projection", *this->projection);
        this->shader->setMat4("view", *this->view);

        glm::mat4 matrix_model;
        //matrix_model = glm::rotate(matrix_model, -3.14f/2.0f, glm::vec3(0.0f, 0.5f, 0.0f));
        matrix_model = glm::translate(matrix_model, this->current_position); // translate it down so it's at the center of the scene
        matrix_model = glm::scale(matrix_model, this->current_scale);	// it's a bit too big for our scene, so scale it down

        this->shader->setMat4("model", matrix_model);
    }

    void draw(){
        this->model->Draw(*this->shader);
    }

    void draw_bullets(){
        for(int i=0;i<this->bullets.size();i++){
            this->bullets[i].pre_draw(this->projection, this->view);
            this->bullets[i].draw();
            this->bullets[i].move();
        }
    }

    void shoot(){
        glm::vec3 fixed_pos = this->current_position;
        fixed_pos.z += 3.0f;
        Bullet bullet(this->current_position);
        this->bullets.push_back(bullet);
    }

    glm::vec3 get_center_collide(){
        return  this->current_position;
    }

    GLfloat get_radio_collide(){
        GLfloat radio = 16.0f;
        return radio;
    }

    void move(int move){
        if(move == (int) GLFW_KEY_W)
            this->current_position.y += 2.0f;
        else if(move == (int) GLFW_KEY_S)
            this->current_position.y -= 2.0f;
        else if(move == (int) GLFW_KEY_A)
            this->current_position.x += 2.0f;
        else if(move == (int) GLFW_KEY_D)
            this->current_position.x -= 2.0f;
    }
};


#endif // ARWING_H
