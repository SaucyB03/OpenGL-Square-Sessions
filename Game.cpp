//
// Created by brado on 3/8/2023.
//

#include "Game.h"
#include "GLFW/glfw3.h"
#include <iostream>

Game::Game(int scWidth, int scHeight){
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    player = new Player(glm::vec2(scWidth/2 - PLAYER_DIM/2, scHeight/2 - PLAYER_DIM/2), glm::vec2(PLAYER_DIM,PLAYER_DIM), glm::vec2(0.0,0.0), 100, scHeight, scHeight);

}

void Game::checkCollisions() {

}

void Game::updateMotion(double deltaTime) {
    player->move(false, 0, false, deltaTime);
}

void Game::renderAll() {
    player->display();
}

void Game::checkInput(GLFWwindow *window, double deltaTime){
    bool jump = false;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        jump = true;
        std::cout << "Key Press: SPACE" << endl;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        player->move(true, false, false, deltaTime);
    }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        std::cout << "Key Press: A" << endl;
    }
}

