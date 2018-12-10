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
    float angle;
    float dtime;
    float rotAngle = (rand() % 360);


    Asteroid() {
        this->shader = new Shader("1.model_loading.vs", "1.model_loading.fs");
        this->model = new Model(FileSystem::getPath("resources/objects/asteroid/10464_Asteroid_v1_Iterations-2.obj"));
        dtime=0.01f;
        angle=3.14f;
        //original_position
        //-1.0f,  1.0f, -1.0f,
        current_position = glm::vec3(1.0f, -1.75f, 0.0f);
        current_scale = glm::vec3(0.01f, 0.01f, 0.01f);
        //current_rotate = glm::vec3(0.0f, 0.01f, 0.0f);
        current_rotate = glm::vec3(0.4f, 0.6f, 0.8f);
    
        //float rotAngle = (rand() % 360);
        

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

    void move(){
        //while(true){
            this->current_position.z += 0.7f*0.16f;
            rotAngle += 0.06f*0.16f;
 
            //angle += 0.06f*0.16f;
            
            std::cout<<this->current_rotate.z<<std::endl;
            //dtime +=0.01f;

        //}
    }
};


#endif // ARWING_H
