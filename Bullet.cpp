//
// Created by brado on 3/23/2023.
//

#include "Bullet.h"
#include <math.h>

Bullet::Bullet(glm::vec2 charPos, float mouseX, float mouseY, int scWidth, int scHeight) : Object(charPos, glm::vec2(10,10), glm::vec2(SPEED * cos(atan((mouseY - charPos.y) / (mouseX - charPos.x))), SPEED * sin(atan((mouseY - charPos.y) / (mouseX - charPos.x)))), true, scWidth, scHeight){

}

Bullet::~Bullet() {

}


