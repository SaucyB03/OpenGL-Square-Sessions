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

    cout << "theta:" << theta / M_PI * 180<< endl;
    cout << "deltas: " << deltaX << ", " << deltaY << endl;
    if(deltaY < 0 && deltaX < 0) {
        return {SPEED * cos(theta+ M_PI / 2), SPEED * sin(theta + M_PI )};
    }else if(deltaX < 0){
        return {SPEED * cos(theta + M_PI / 2), SPEED * sin(theta)};
    }else if(deltaY < 0){
        return {SPEED * cos(theta), SPEED * sin(theta + M_PI / 2)};
    }else{
        return {SPEED * cos(theta), SPEED * sin(theta)};
    }

}

Bullet::Bullet(glm::vec2 charPos, double mouseX, double mouseY, int scWidth, int scHeight) : Object(charPos, glm::vec2(10,10), calcVelocity(charPos, mouseX, mouseY), true, scWidth, scHeight){

}

Bullet::~Bullet() {

}

