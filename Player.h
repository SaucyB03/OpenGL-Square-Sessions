//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_PLAYER_H
#define M3OE_BKSOUCY_PLAYER_H

#include <vector>

#include "Object.h"
#include "Bullet.h"

const float MAXPIXPERSEC = 400;
const float JUMP_VEL = 1000;


class Player : public Object {
private:
    int health;
    int damageTaken;
    int damageDone;
    bool grounded;
    vector<Bullet> shots;
public:
    Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::mat4x3 vecColor, int health, int scWidth, int scHeight);
    ~Player();

    void changeHealth(int deltaHealth);
    void move(int move, bool jump, double deltaTime);
    int getHealth();
    int getDamageDone();
    int getDamageTaken();
};


#endif //M3OE_BKSOUCY_PLAYER_H
