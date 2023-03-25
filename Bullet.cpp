//
// Created by brado on 3/23/2023.
//

#include "Bullet.h"
#include <cmath>

glm::vec2 Bullet::calcVelocity(glm::vec2 charPos, float mouseX, float mouseY) {
    double deltaX = mouseX - charPos.x;
    double deltaY = mouseY - charPos.y;
    double hypo = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    double theta = abs(atan(deltaY / deltaX));


    if(deltaY < 0 && deltaX < 0) {
        theta = M_PI + theta;
    }else if(deltaX < 0){
        theta = M_PI - theta;
    }else if(deltaY < 0){
        theta = 2*M_PI - theta;
    }

    return {SPEED * cos(theta), SPEED * sin(theta)};

}

Bullet::Bullet(glm::vec2 charPos, double mouseX, double mouseY, int scWidth, int scHeight) : Object(charPos, glm::vec2(10,10), calcVelocity(charPos, mouseX, mouseY), true, scWidth, scHeight){

}

Bullet::~Bullet() {

}

int Bullet::getDamage() {
    return DAMAGE;
}
