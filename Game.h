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

    GLFWwindow* window;

    vector<Object> heals;
    vector<Object> spikes;

public:
    Game(int SC_WIDTH, int SC_HEIGHT, GLFWwindow* window);

    void displayMenu();
    bool getMenuStatus();

    int getScWidth() const;
    int getScHeight() const;

    void beginGame();

    void checkInput(GLFWwindow *window);
};





#endif //M3OE_BKSOUCY_GAME_H
