//
// Created by brado on 3/8/2023.
//

#include "Player.h"
#include "Object.h"
#include "Game.h"


Player::Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, int health, int scWidth, int scHeight) {
    this->position = position;
    this->scale = scale;
    this->velocity = velocity;
    this->health = health;
    this->scWidth = scWidth;
    this->scHeight = scHeight;


    float verts[] = {
            scale.x + position.x,  scale.y + position.y, 0.0f,  // top right
            scale.x + position.x, -scale.y + position.y, 0.0f,  // bottom right
            -scale.x + position.x, -scale.y + position.y, 0.0f,  // bottom left
            -scale.x + position.x,  scale.y + position.y, 0.0f,   // top left
    };

    int i;
    for(i = 0; i < sizeof(vertices); ++i){
        if(i % 3 == 0){
            vertices[i] = verts[i] / this->scWidth;
        }else{
            vertices[i] = verts[i] / this->scHeight;
        }
    }


    assignBuffandArr(vertices, indices);
}

Player::~Player() {

}

void Player::changeHealth(int deltaHealth) {
    this->health += deltaHealth;
}

void Player::move(bool grounded, bool move, bool jump, float deltaTime) {
    /*For move:
     * True = Right
     * False = Left */

    if(move){
        this->position.x += MAXPIXPERSEC * deltaTime;
    }else{
        this->position.x -= MAXPIXPERSEC * deltaTime;
    }

    if(grounded && jump){
        velocity.y += jumpVel;
    }
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

