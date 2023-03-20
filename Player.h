//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_PLAYER_H
#define M3OE_BKSOUCY_PLAYER_H

#include "Object.h"

class Player : public Object {
private:
    int health;
public:
    Player();
    Player(glm::vec2 position, glm::vec2 scale, Shape shape, int health);
    ~Player();

    void changeHealth(int deltaHealth);
};


#endif //M3OE_BKSOUCY_PLAYER_H
