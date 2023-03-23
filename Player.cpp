//
// Created by brado on 3/8/2023.
//

#include "Player.h"

Player::Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::mat4x3 vecColor, int health, int scWidth, int scHeight) : Object(position, scale, velocity, true, scWidth, scHeight) {
    this->health = health;
    this->damageTaken = 0;
    this->damageDone = 0;
    this->grounded = true;
    this->shots = new vector<Bullet>();
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

    if(move == 1){
        this->position.x -= MAXPIXPERSEC * deltaTime;
    }else if (move == 2){
        this->position.x += MAXPIXPERSEC * deltaTime;
    }

    if(!grounded){
        cout << position.y << endl;
        if(position.y > 0  && velocity.y < 0){
            velocity.y -= APPARENT_GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;

        }else if(velocity.y > 0){
            velocity.y -= APPARENT_GRAVITY * deltaTime;
            position.y += velocity.y * deltaTime;
        }else{
            this->grounded = true;
        }
    }

    if(grounded && jump){
        this->grounded = false;
        velocity.y += JUMP_VEL;
    }else if (grounded){
        //cout << velocity.y<< endl;
        velocity.y = 0;
    }
}

void Player::shoot(double xPos, double yPos){
    shots->push_back(new Bullet(position, (xPos+1)/2 * scWidth, (yPos+1) /2 * scHeight, scWidth, scHeight));
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

