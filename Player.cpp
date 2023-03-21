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
        velocity.y += JUMP_VEL;
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

