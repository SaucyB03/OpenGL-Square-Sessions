//
// Created by brado on 3/8/2023.
//

#include "Game.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Game::Game(int SC_WIDTH, int SC_HEIGHT, GLFWwindow* window) {
    this-> SC_WIDTH = SC_WIDTH;
    this-> SC_HEIGHT = SC_HEIGHT;
    this->window = window;
//    menu = true;
//    displayMenu();
}

void Game::displayMenu(){
    //system("py ./displayText.py " +  + );
    //ODO make python file that displays text, pass menu information with cords and display it
    // information about this can be found: https://stackoverflow.com/questions/63836707/how-to-render-text-with-pyopengl
}

bool Game::getMenuStatus() {
    return menu;
}

int Game::getScWidth() const {
    return SC_WIDTH;
}

int Game::getScHeight() const{
    return SC_HEIGHT;
}

void Game::beginGame() {

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
