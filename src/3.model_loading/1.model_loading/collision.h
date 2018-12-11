#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include "asteroid.h"
#include "bullet.h"
#include "arwing.h"

using namespace std;

void collision_asteroid_bullet(vector<Asteroid> &asteroids, vector<Bullet> &bullets, Arwing *starship){
    int index_bullet = 0;
    for(Asteroid &asteroid : asteroids){
        bool collided = false;
        for(Bullet &bullet: bullets){
            glm::vec3 bullet_center = bullet.get_center_collide();
            GLfloat bullet_radio = bullet.get_radio_collide();
            if(asteroid.detect_collision(bullet_center, bullet_radio)){
                bullets.erase(bullets.begin()+index_bullet);
                asteroid.destroyed = true;
                collided = true;
                //cout << "collideeed" << endl;
                break;
            }
            index_bullet++;
        }
        glm::vec3 center_starship = starship->get_center_collide();
        GLfloat radio_starship = starship->get_radio_collide();
        if(asteroid.detect_collision(center_starship, radio_starship)){
            cout << "collidsaa" << endl;
            exit(0);
        }
    }
}

#endif // COLLISION_H
