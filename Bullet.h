//
// Created by brado on 3/23/2023.
//

#ifndef M3OE_BKSOUCY_BULLET_H
#define M3OE_BKSOUCY_BULLET_H

#include "glm/glm.hpp"

#include "Object.h"

const float SPEED = 1200;

class Bullet : public Object{
private:
    const int DAMAGE = 1;
    glm::vec2 calcVelocity(glm::vec2 charPos, float mouseX, float mouseY);

public:
    Bullet(glm::vec2 charPos, double mouseX, double mouseY, int scWidth, int scHeight);

    ~Bullet();

    int getDamage();
};


#endif //M3OE_BKSOUCY_BULLET_H
