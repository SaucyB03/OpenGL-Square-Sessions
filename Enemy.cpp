//
// Created by brado on 3/21/2023.
//

#include "Enemy.h"

/*Constructor
 * Initializes enemy information as well as initialize parent object class
 */
Enemy::Enemy(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, int health, int scWidth, int scHeight) : Object(position, scale, velocity, color, true, scWidth, scHeight) {
    this->health = health;
    this->grounded = true;
    this->dropPlat = 0;
}

Enemy::~Enemy() {

}

/*change Health
 * changes the enemies health by the inputted value
 */
bool Enemy::changeHealth(int deltaHealth) {
    health -= deltaHealth;

    //if this object is dead then it returns true so the game class knows to delete it
    if(health <= 0){
        return true;
    }
    return false;
}

/* Enemy move
 * moves based off character location, can jump but cant quite reach next platform
 * to give you a slight advantage since before it was pretty hard to go very far
 */
void Enemy::move(glm::vec2 playerPos, glm::vec2 playerScale, int platThickness, double deltaTime) {

    //Move L/R depending on where the player is on screen
    if (position.x > playerPos.x + playerScale.x) {
        position.x -= MAXPIXPERSEC * deltaTime;
    } else if (position.x + scale.x < playerPos.x) {
        position.x += MAXPIXPERSEC * deltaTime;
    }

    //if not grounded then calculate freefall physics
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

    //Determine if the player is beneath the enemy and needs to drop platforms
    if(position.y < playerPos.y - platThickness  && abs(position.x - (playerPos.x + playerScale.x / 2)) <= scale.x * 3 && grounded){
        grounded = false;
        velocity.y = JUMP_VEL;
    }else if(position.y > playerPos.y + playerScale.y && abs(position.x - (playerPos.x + playerScale.x / 2)) <= scale.x * 3 && grounded){
        grounded = false;
        setDropPlat(platThickness*2);
    }

    //Prevents the enemy from falling through multiple platforms
    if(dropPlat != 0 && position.y < dropPlat ){
        dropPlat = 0;
    }
}

/*getDropPlat
 * returns dropPlat
 */
double Enemy::getDropPlat() {
    return dropPlat;
}

/*getHealth
 * returns the enemies current health
 */
int Enemy::getHealth() {
    return health;
}

/*setGrounded
 * sets if teh player is grounded
 */
void Enemy::setGrounded(bool grounded) {
    this->grounded = grounded;
}

/*setDropPlat
 * sets dropPlat to be below its current platform, so the enemy knows how far it can freefal
 * before being able to interact with platforms again
 */
void Enemy::setDropPlat(int dropSpace) {
    this->dropPlat = position.y - dropSpace;
}

