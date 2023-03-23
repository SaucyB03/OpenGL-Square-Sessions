//
// Created by brado on 3/23/2023.
//

#ifndef M3OE_BKSOUCY_BULLET_H
#define M3OE_BKSOUCY_BULLET_H

#include "glm/glm.hpp"

#include "Object.h"

const float SPEED = 3000;

class Bullet : public Object{
    ~Bullet();

public:
    Bullet(glm::vec2 charPos, float mouseX, float mouseY, int scWidth, int scHeight);
};


#endif //M3OE_BKSOUCY_BULLET_H
