//
// Created by brado on 3/21/2023.
//

#include "Enemy.h"

Enemy::Enemy(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, int health, int scWidth, int scHeight) : Object(position, scale, velocity, color, true, scWidth, scHeight) {
    this->health = health;
    this->grounded = true;
    this->dropPlat = 0;
}

Enemy::~Enemy() {

}

bool Enemy::changeHealth(int deltaHealth) {
    health -= deltaHealth;

    //if this object is dead then it returns true so the game class knows to delete it
    if(health <= 0){
        return true;
    }
    return false;
}

void Enemy::move(glm::vec2 playerPos, glm::vec2 playerScale, int platThickness, double deltaTime) {

    if (position.x > playerPos.x + playerScale.x) {
        position.x -= MAXPIXPERSEC * deltaTime;
    } else if (position.x + scale.x < playerPos.x) {
        position.x += MAXPIXPERSEC * deltaTime;
    }


    if(!grounded){
        if(position.y > 0  && velocity.y <= 0){
            velocity.y -= APPARENT_GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;

        }else if(velocity.y >= 0){
            velocity.y -= APPARENT_GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;
        }else{
            grounded = true;
            velocity.y = 0;
        }
    }else{
        velocity.y = 0;
    }

    if(position.y < playerPos.y - platThickness  && abs(position.x - (playerPos.x + playerScale.x / 2)) <= scale.x * 3 && grounded){
        grounded = false;
        velocity.y = JUMP_VEL;
    }else if(position.y > playerPos.y + playerScale.y && abs(position.x - (playerPos.x + playerScale.x / 2)) <= scale.x * 3 && grounded){
        grounded = false;
        setDropPlat(platThickness*2);
    }


    if(dropPlat != 0 && position.y < dropPlat ){
        dropPlat = 0;
    }
}

double Enemy::getDropPlat() {
    return dropPlat;
}

bool Enemy::getGrounded() {
    return grounded;
}

int Enemy::getHealth() {
    return health;
}

void Enemy::setGrounded(bool grounded) {
    this->grounded = grounded;
}

void Enemy::setDropPlat(int dropSpace) {
    this->dropPlat = position.y - dropSpace;
}

