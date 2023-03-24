//
// Created by brado on 3/23/2023.
//

#include "Bullet.h"
#include <cmath>

glm::vec2 Bullet::calcVelocity(glm::vec2 charPos, float mouseX, float mouseY) {
    double deltaX = mouseX - charPos.x;
    double deltaY = mouseY - charPos.y;
    double hypo = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    double theta = atan(deltaY / deltaX);

    return {SPEED * cos(theta), SPEED * sin(theta)};
}

Bullet::Bullet(glm::vec2 charPos, double mouseX, double mouseY, int scWidth, int scHeight) : Object(charPos, glm::vec2(10,10), calcVelocity(charPos, mouseX, mouseY), true, scWidth, scHeight){

}

Bullet::~Bullet() {

}

