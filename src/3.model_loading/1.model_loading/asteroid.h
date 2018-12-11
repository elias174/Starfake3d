#ifndef ASTEROID_H
#define ASTEROID_H
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
#include <random>


GLfloat distance_points(glm::vec3 first, glm::vec3 second){
    GLfloat first_component = pow(second.x-first.x, 2.0f);
    GLfloat second_component = pow(second.y-first.y, 2.0f);
    GLfloat third_component = pow(second.z-first.z, 2.0f);
    return sqrt(first_component+second_component+third_component);
}

class Asteroid
{
public:
    Shader *shader;
    Model *model;
    glm::mat4 *projection;
    glm::mat4 *view;
    glm::mat4 *c_matrix_model;
    glm::vec3 current_position;
    glm::vec3 current_scale;
    glm::vec3 current_rotate;
    bool destroyed;
    float angle;
    float dtime;
    float rotAngle = (rand() % 360);
    //float rand_pos;
    float rand_pos = -1.75f;
        
    Asteroid() {
        this->shader = new Shader("1.model_loading.vs", "1.model_loading.fs");
        this->model = new Model(FileSystem::getPath("resources/objects/SmallAsteroid/Small\ Asteroid.obj"));

        std::random_device rd;

        std::mt19937 e2(rd());
        int min = -90, max = 90 ;
        std::uniform_int_distribution<int> dist(min,max);
        float rand_pos = dist(e2)/1.0f;

        current_position = glm::vec3(rand_pos,-1.75f, 100.0f);
        current_scale = glm::vec3(3.0f, 3.0f, 3.0f);
        current_rotate = glm::vec3(0.4f, 0.6f, 0.8f);
        destroyed = false;
    }

    void pre_draw(glm::mat4 *projection, glm::mat4 *view){
        this->projection = projection;
        this->view = view;
        this->shader->setMat4("projection", *this->projection);
        this->shader->setMat4("view", *this->view);

        glm::mat4 matrix_model;
        matrix_model = glm::translate(matrix_model, this->current_position); // translate it down so it's at the center of the scene
        matrix_model = glm::scale(matrix_model, this->current_scale);	// it's a bit too big for our scene, so scale it down
        matrix_model = glm::rotate(matrix_model,rotAngle, this->current_rotate);   // it's a bit too big for our scene, so scale it down
        
        this->shader->setMat4("model", matrix_model);
    }

    void draw(){
        this->model->Draw(*this->shader);
    }

    glm::vec3 get_center_collide(){
        return  this->current_position;
    }

    GLfloat get_radio_collide(){
        GLfloat radio = 8.0f;
        return radio;
    }

    bool detect_collision(glm::vec3 center, GLfloat radio){
        return radio+get_radio_collide() > distance_points(get_center_collide(), center);
    }

    void move(){
    //while(true){
            this->current_position.z -= 1.0f*0.16f;
            rotAngle += 0.06f*0.16f;
            //angle += 0.06f*0.16f;
            //dtime +=0.01f;

        //}
    }
};



#endif // ARWING_H
