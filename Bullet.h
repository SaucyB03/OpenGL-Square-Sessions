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
    /*calcVelocity
     * calculates the velocity components of the bullet so that it travels towards the
     * mouse location at a given speed
     */
    glm::vec2 calcVelocity(glm::vec2 charPos, float mouseX, float mouseY);

public:
    /*Constructor
     * Initializes the bullets information, and initializes the parent object class
     */
    Bullet(glm::vec2 charPos, double mouseX, double mouseY, glm::vec3 color, int scWidth, int scHeight);
    ~Bullet();

    /*getDamage
     * returns the damage that the bullet does
     */
    int getDamage();
};


#endif //M3OE_BKSOUCY_BULLET_H
