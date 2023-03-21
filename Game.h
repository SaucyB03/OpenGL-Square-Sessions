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
    int SC_WIDTH;
    int SC_HEIGHT;
    bool menu;

    Player* player;
    vector<Object> enemies;

public:
    Game(int SC_WIDTH, int SC_HEIGHT);

    void renderAll();

    void checkInput(GLFWwindow *window);
};





#endif //M3OE_BKSOUCY_GAME_H
