//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_GAME_H
#define M3OE_BKSOUCY_GAME_H

#include <vector>
#include <memory>
#include <iostream>
#include <random>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

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
    glm::vec3 enemyColor = {1.0f, 0.5f, 0.0f};
    glm::vec3 platformColor = {0.0,0.0,0.0};

    void defeatedEnemy(int index);
    glm::vec2 randEnemyPosInit();

public:
    Game(int scWidth, int scHeight);

    void checkCollisions(double deltaTime);
    void updateMotion(vector<bool> motion, double deltaTime);

    //Shader returnShader();

    void renderAll();
    vector<bool> checkKeyInput(GLFWwindow *window, double deltaTime);
    void checkMouseInput(GLFWwindow *window, double xPos, double yPos, double deltaTime);

    void gameOver(GLFWwindow *window);
};





#endif //M3OE_BKSOUCY_GAME_H
