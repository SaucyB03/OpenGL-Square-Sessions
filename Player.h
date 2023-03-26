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
    /*Player Move
     * Based off user input this method calculates physics to allow for the character to
     * move L/R or jump and utilizes the delta Time input to make it consistent
     */
    void move(int move, bool jump, double deltaTime);
    /*Shoot
     * when called initializes a bullet object and stores it in shots
     */
    void shoot(double xPos, double yPos);
    /*deleteShot
     * erases the shot at index, index
     */
    void deleteShot(int index);

    /*getCurrentShots
     * returns a vector of the current Bullet objects
     */
    vector<Bullet*>* getCurrentShots();
    /*getDropPlat
     * returns dropPlat the bottom of the platform the player rests on
     */
    double getDropPlat();
    /*getGrounded
     * returns whether or not the player is grounded
     */
    bool getGrounded();
    /*getHealth
     * returns the players current health
     */
    double getHealth();
    /*getDamageDone
     * returns the damage to enemies the player has done
     */
    int getDamageDone();
    /*getDamageTaken
     * returns the total damage the player has taken
     */
    int getDamageTaken();

    /*setGrounded
     * sets whether the player is grounded or not
     */
    void setGrounded(bool grounded);
    /* setDropPlat
     * sets the y position the player can freefall to before it
     * will interact with platforms again
     */
    void setDropPlat(int dropSpace);
};


#endif //M3OE_BKSOUCY_PLAYER_H
