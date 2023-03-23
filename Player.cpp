//
// Created by brado on 3/8/2023.
//

#include "Player.h"
#include "Object.h"

Player::Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, int health, int scWidth, int scHeight) : Object(position, scale, velocity, true, scWidth, scHeight) {
    this->health = health;
    this->damageTaken = 0;
    this->damageDone = 0;
}

Player::~Player() {

}

void Player::changeHealth(int deltaHealth) {
    this->health += deltaHealth;
}

void Player::move(bool grounded, int move, bool jump, double deltaTime) {

    glm::vec2 oldPos = position;
    /*For move:
     * 0 = idle
     * 1 = left
     * 2 = right*/

    if(move == 1){
        this->position.x += MAXPIXPERSEC * deltaTime;
    }else if (move == 2){
        this->position.x -= MAXPIXPERSEC * deltaTime;
    }

    if(!grounded){
        if(position.y > -10){
            velocity.y -= GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;
        }
    }

    if(grounded && jump){
        grounded = false;
        velocity.y += JUMP_VEL;
    }else if (grounded){
        velocity.y = 0;
    }

    Object::move(glm::vec2(10, 0));

}

int Player::getHealth() {
    return health;
}

int Player::getDamageDone() {
    return damageDone;
}

int Player::getDamageTaken() {
    return damageTaken;
}

