//
// Created by brado on 3/8/2023.
//

#include "Player.h"

Player::Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::mat4x3 vecColor, int health, int scWidth, int scHeight) : Object(position, scale, velocity, true, scWidth, scHeight) {
    this->health = health;
    this->damageTaken = 0;
    this->damageDone = 0;
    this->grounded = true;
    this->dropPlat = 0;
    this->shots = new vector<Bullet*>();
}

Player::~Player() {

}

void Player::changeHealth(int deltaHealth) {
    this->health += deltaHealth;
}

void Player::move(int move, bool jump, double deltaTime) {

    /*For move:
     * 0 = idle
     * 1 = left
     * 2 = right*/

    if(dropPlat != 0 && grounded){
        grounded = false;
    }

    if(move == 1 && position.x > 0.0){
        this->position.x -= MAXPIXPERSEC * deltaTime;
    }else if (move == 2 && position.x + scale.x < scWidth){
        this->position.x += MAXPIXPERSEC * deltaTime;
    }

    if(!grounded){
        if(position.y > 0  && velocity.y <= 0){
            velocity.y -= APPARENT_GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;

        }else if(velocity.y >= 0){
            velocity.y -= APPARENT_GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;
        }else{
            this->grounded = true;
        }
    }

    if(grounded && jump){
        this->grounded = false;
        velocity.y = JUMP_VEL;
    }else if (grounded){
        velocity.y = 0;
    }

    if(dropPlat != 0 && position.y < dropPlat ){
        dropPlat = 0;
    }
}

void Player::shoot(double xPos, double yPos){

    shots->push_back(new Bullet({position.x + scale.x/2, position.y + scale.y/2}, xPos, yPos, scWidth, scHeight));
}

void Player::deleteShot(int index) {
    this->shots->erase(shots->begin() + index);
}

vector<Bullet*>* Player::getCurrentShots() {
    return shots;
}

double Player::getDropPlat() {
    return dropPlat;
}

bool Player::getGrounded() {
    return grounded;
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

void Player::setGrounded(bool grounded) {
    this->grounded = grounded;
}

void Player::setDropPlat(int dropSpace) {
    this->dropPlat = position.y - dropSpace;
}

