//
// Created by brado on 3/8/2023.
//

#include "Game.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Game::Game(int SC_WIDTH, int SC_HEIGHT){
    this-> SC_WIDTH = SC_WIDTH;
    this-> SC_HEIGHT = SC_HEIGHT;
    player = new Player(glm::vec2(0.0,0.0), glm::vec2(500,500), glm::vec2(0.0,0.0), 100, SC_WIDTH, SC_HEIGHT);
}

void Game::renderAll() {
    player->display();
}

void Game::checkInput(GLFWwindow *window){
    bool jump = false;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        jump = true;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){

    }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){

    }
}
