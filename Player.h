//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_PLAYER_H
#define M3OE_BKSOUCY_PLAYER_H

#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Object.h"
#include "Bullet.h"


class Player : public Object {
private:
    const float MAXPIXPERSEC = 400;
    const float JUMP_VEL = 1000;
    double health;
    double damageTaken;
    int damageDone;
    bool grounded;
    double dropPlat;
    bool canJump = true;
    vector<Bullet*>* shots;

    glm::vec3 bulletColor = {0.5, 0.5, 0.5};

public:
    /*Constructor
     * initializes players variables and calls the parent Object class to be initialized
     */
    Player(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, int health, int scWidth, int scHeight);
    ~Player();

    /* change Health
     * adjusts players health when player takes damage
     */
    void changeHealth(double deltaHealth);
    /* change Health
     * adjusts players health when player takes damage
     */
    void addDamageDone(int damage);
    void move(int move, bool jump, double deltaTime);
    void shoot(double xPos, double yPos);

    void deleteShot(int index);

    vector<Bullet*>* getCurrentShots();
    double getDropPlat();
    bool getGrounded();
    float getSpeed();
    double getHealth();
    int getDamageDone();
    int getDamageTaken();

    void setGrounded(bool grounded);
    void setDropPlat(int dropSpace);
    void setCanJump(bool canJump);
};


#endif //M3OE_BKSOUCY_PLAYER_H
