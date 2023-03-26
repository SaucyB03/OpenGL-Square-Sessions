//
// Created by brado on 3/21/2023.
//

#ifndef M3OE_BKSOUCY_ENEMY_H
#define M3OE_BKSOUCY_ENEMY_H

#include "Object.h"



class Enemy : public Object {
private:
    const float MAXPIXPERSEC = 250;
    const float JUMP_VEL = 800;
    int health;
    bool grounded;
    double dropPlat;
public:
    /*Constructor
     * Initializes enemy information as well as initialize parent object class
     */
    Enemy(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, int health, int scWidth, int scHeight);
    ~Enemy();

    /*change Health
     * changes the enemies health by the inputted value
     */
    bool changeHealth(int deltaHealth);
    /* Enemy move
     * moves based off character location, can jump but cant quite reach next platform
     * to give you a slight advantage since before it was pretty hard to go very far
     */
    void move(glm::vec2 playerPos, glm::vec2 playerScale, int platThickness, double deltaTime);

    /*getDropPlat
     * returns dropPlat
     */
    double getDropPlat();
    /*getHealth
     * returns the enemies current health
     */
    int getHealth();

    /*setGrounded
     * sets if teh player is grounded
     */
    void setGrounded(bool grounded);
    /*setDropPlat
     * sets dropPlat to be below its current platform, so the enemy knows how far it can freefal
     * before being able to interact with platforms again
     */
    void setDropPlat(int dropSpace);
};



#endif //M3OE_BKSOUCY_ENEMY_H
