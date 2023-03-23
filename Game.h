//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_GAME_H
#define M3OE_BKSOUCY_GAME_H

#include <vector>
#include "Object.h"
#include "Player.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

class Game {
private:
    const int PLAYER_DIM = 50;
    int scWidth;
    int scHeight;
    bool menu;

    Player* player;
    Object* ground;
    vector<Object> enemies;
    vector<Object> platforms;

public:
    Game(int scWidth, int scHeight);

    void checkCollisions();
    void updateMotion(double deltaTime);

    void renderAll();
    void checkInput(GLFWwindow *window, double deltaTime);
};





#endif //M3OE_BKSOUCY_GAME_H
