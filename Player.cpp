//
// Created by brado on 3/8/2023.
//

#include "Player.h"

/*Constructor
 * initializes players variables and calls the parent Object class to be initialized
 */
Player::Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, int health, int scWidth, int scHeight) : Object(position, scale, velocity, color, true, scWidth, scHeight) {
    this->health = health;
    this->damageTaken = 0;
    this->damageDone = 0;
    this->grounded = true;
    this->dropPlat = 0;
    this->shots = new vector<Bullet*>();
}

Player::~Player() {

}

/* change Health
 * adjusts players health when player takes damage
 */
void Player::changeHealth(double deltaHealth) {
    health += deltaHealth;
    damageTaken -= deltaHealth;
}

/*addDamageDone
 * When player hits enemy then it increments damage done by the inputted damage
 */
void Player::addDamageDone(int damage) {
    damageDone += damage;
}

/*Player Move
 * Based off user input this method calculates physics to allow for the character to
 * move L/R or jump and utilizes the delta Time input to make it consistent
 */
void Player::move(int move, bool jump, double deltaTime) {

    /*For move:
     * 0 = idle
     * 1 = left
     * 2 = right*/

    //If player is dropping off the platform then grounded = false so the player can fall off it
    if(dropPlat != 0 && grounded){
        grounded = false;
    }

    //if user inputs L/R movement then the player moves that direction
    if(move == 1 && position.x > 0.0){
        this->position.x -= MAXPIXPERSEC * deltaTime;
    }else if (move == 2 && position.x + scale.x < scWidth){
        this->position.x += MAXPIXPERSEC * deltaTime;
    }

    //If the player isn't grounded calculate freefall physics
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

    if(grounded && jump && canJump){
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
    shots->push_back(new Bullet({position.x + scale.x/2, position.y + scale.y / 2}, xPos, yPos, bulletColor, scWidth, scHeight));
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

float Player::getSpeed() {
    return MAXPIXPERSEC;
}

double Player::getHealth() {
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

void Player::setCanJump(bool canJump) {
    this->canJump = canJump;
}

