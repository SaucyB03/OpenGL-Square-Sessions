//
// Created by brado on 3/8/2023.
//

#include "Game.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Game::Game(int scWidth, int scHeight){
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    player = new Player(glm::vec2(0.0,0.0), glm::vec2(scHeight/2,scHeight/2), glm::vec2(0.0,0.0), 100, scHeight, scHeight);
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
