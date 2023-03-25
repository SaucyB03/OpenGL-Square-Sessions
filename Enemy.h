//
// Created by brado on 3/21/2023.
//

#ifndef M3OE_BKSOUCY_ENEMY_H
#define M3OE_BKSOUCY_ENEMY_H

#include "Object.h"



class Enemy : public Object {
private:
    const float MAXPIXPERSEC = 300;
    const float JUMP_VEL = 1000;
    int health;
    bool grounded;
    double dropPlat;
    bool jump;

public:
    Enemy(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::mat4x3 vecColor, int health, int scWidth, int scHeight);
    ~Enemy();

    bool changeHealth(int deltaHealth);
    void move(glm::vec2 playerPos, glm::vec2 playerScale, int platThickness, double deltaTime);

    double getDropPlat();
    bool getGrounded();
    int getHealth();

    void setGrounded(bool grounded);
    void setDropPlat(int dropSpace);
};



#endif //M3OE_BKSOUCY_ENEMY_H
