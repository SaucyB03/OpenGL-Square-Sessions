//
// Created by brado on 3/23/2023.
//

#include "Bullet.h"
#include <cmath>

/*calcVelocity
 * calculates the velocity components of the bullet so that it travels towards the
 * mouse location at a given speed
 */
glm::vec2 Bullet::calcVelocity(glm::vec2 charPos, float mouseX, float mouseY) {
    //calculates theta
    double deltaX = mouseX - charPos.x;
    double deltaY = mouseY - charPos.y;
    double theta = abs(atan(deltaY / deltaX));

    //Since theta is only between 0 - PI/2
    //We adjust so it can be between 0 - 2PI
    if(deltaY < 0 && deltaX < 0) {
        theta = M_PI + theta;
    }else if(deltaX < 0){
        theta = M_PI - theta;
    }else if(deltaY < 0){
        theta = 2*M_PI - theta;
    }

    return {SPEED * cos(theta), SPEED * sin(theta)};

}

/*Constructor
 * Initializes the bullets information, and initializes the parent object class
 */
Bullet::Bullet(glm::vec2 charPos, double mouseX, double mouseY, glm::vec3 color, int scWidth, int scHeight) : Object(charPos, glm::vec2(10,10), calcVelocity(charPos, mouseX, mouseY), color, true, scWidth, scHeight){

}

Bullet::~Bullet() {

}

/*getDamage
 * returns the damage that the bullet does
 */
int Bullet::getDamage() {
    return DAMAGE;
}
