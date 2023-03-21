//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_PLAYER_H
#define M3OE_BKSOUCY_PLAYER_H

#include "Object.h"

const float MAXPIXPERSEC = 5;
const float JUMP_VEL = 10;

class Player : public Object {
private:
    int health;
    int damageTaken;
    int damageDone;
public:
    Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, int health, int scWidth, int scHeight);
    ~Player();

    void changeHealth(int deltaHealth);
    void move(bool groundContact, bool move, bool jump, float deltaTime);
    int getHealth();
    int getDamageDone();
    int getDamageTaken();
};


#endif //M3OE_BKSOUCY_PLAYER_H
