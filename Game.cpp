//
// Created by brado on 3/8/2023.
//

#include "Game.h"

Game::Game(int scWidth, int scHeight){
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    player = new Player(glm::vec2(0.0 , 0.0), glm::vec2(scWidth / 10,scHeight / 10), glm::vec2(0.0,0.0), playerColor, 100, scHeight, scHeight);

}

void Game::checkCollisions() {

}

void Game::updateMotion(vector<bool> motion, double deltaTime) {
    if(motion[1]){
        player->move(1, motion[0], deltaTime);
    }else if(motion[2]){
        player->move(2, motion[0], deltaTime);
    }else{
        player->move(0, motion[0], deltaTime);
    }
}


void Game::renderAll() {
    player->display();
}

vector<bool> Game::checkInput(GLFWwindow *window, double deltaTime){
    vector<bool> keys= {false,false,false};
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        keys[0] = true;

    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        keys[2] = true;
    }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        keys[1] = true;
    }
    return keys;
}