//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_GAME_H
#define M3OE_BKSOUCY_GAME_H

#include <vector>
#include <memory>
#include <iostream>
#include <random>

//OpenGL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

//Game Objects
#include "ShaderManager.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"


using namespace std;

class Game {
private:
    const int PLAYER_DIM = 50;
    const int NUM_PLAT_LEVELS = 4;
    const int PLAT_THICKNESS = 50;
    const int COLL_BUFFER = 1;
    const int NUM_PER_BURST = 100;
    const double COOLDOWN = 0.5;
    int scWidth;
    int scHeight;
    bool endGame;

    int numSpawn = 1;
    int numWaves = 1;

    int shotsInBurst = 0;
    double shotCoolDown = 0;

    double totalTime = 0;

    Player* player;
    vector<Enemy*> enemies;
    vector<Object*> platforms;

    ShaderManager shaderManager;

    glm::vec3 playerColor = {1.0f, 0.5f, 0.2f};
    glm::vec3 enemyColor = {1.0f, 0.0f, 0.0f};
    glm::vec3 platformColor = {0.0,0.0,0.0};

    void defeatedEnemy(int index);
    glm::vec2 randEnemyPosInit();

public:
    Game(int scWidth, int scHeight);

    /*Check Collisions:
     * Checks to see if there's any collisions between the objects
     * If I could change any method it would be this one, there's definitely a better way than what I did here
     */
    void checkCollisions(double deltaTime);
    /*Update Motion
    * Calls each of the objects and tells it that it should move and how long its been since last frame to get consistent movement
    * As for player the direction is based off user input
    * As for enemy the direction is based off the player's location, so it can move towards it
    */
    void updateMotion(vector<bool> motion, double deltaTime);

    /*Render All
     * Pretty self-explainitory it renders all the objects onto the screen so you can see them,
     * Called every frame to update the object movement
     */
    void renderAll();
    /*Check Key Input
     * Checks if any keys have been pressed and returns the inputs as a bool vector
     */
    vector<bool> checkKeyInput(GLFWwindow *window, double deltaTime);
    /*Check mouse input
     * Checks to see if the left mouse button is clicked and shoots
     * Shooting occurs in bursts of NUM_PER_BURST
     * and has a cooldown between burst of COOLDOWN seconds
     */
    void checkMouseInput(GLFWwindow *window, double xPos, double yPos, double deltaTime);

    /* Game Over
     * if the game is over a.k.a the player is dead then the window should close
     */
    void gameOver(GLFWwindow *window);
    /* Game Info
     * Retrieves the player info from the game and returns it as a vector of strings
     */
    vector<string> gameInfo();
};


#endif //M3OE_BKSOUCY_GAME_H
