//
// Created by brado on 3/8/2023.
//

#include "Game.h"

Game::Game(int scWidth, int scHeight){
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    player = new Player(glm::vec2(0.0, 0.0), glm::vec2(0.5,0.5), glm::vec2(0.0,0.0), playerColor, 100, scHeight, scHeight);

}

void Game::checkCollisions() {

}

void Game::updateMotion(double deltaTime) {
    player->move(false, 0, false, deltaTime);
}
//
//Shader Game::returnShader() {
//    return shader;
//}

void Game::renderAll() {
//    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
//    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//    shader->setUniformMat4("transform", transform);
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