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
    int i;
    if(motion[1]){
        player->move(1, motion[0], deltaTime);
    }else if(motion[2]){
        player->move(2, motion[0], deltaTime);
    }else{
        player->move(0, motion[0], deltaTime);
    }
    vector<Bullet*>* shots = player->getCurrentShots();
    for(i = 0; i < shots->size(); ++i){
        shots->at(i)->move(deltaTime);
    }
}


void Game::renderAll() {
    int i;
    player->display();

    vector<Bullet*>* shots = player->getCurrentShots();
    for(i = 0; i < shots->size(); ++i){
        shots->at(i)->display();
    }
}

vector<bool> Game::checkKeyInput(GLFWwindow *window, double deltaTime){
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

void Game::checkMouseInput(GLFWwindow *window, double xPos, double yPos) {
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)){
        cout << "x: " << xPos << ", y: " << yPos << endl;
        player->shoot(xPos, yPos);
    }
}
