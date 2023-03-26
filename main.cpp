//spinesquare

#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "Game.h"

using namespace std;


const int SC_WIDTH = 1600;
const int SC_HEIGHT = 1600;

//map<const char*, Shader> ShaderResources::allShaders = *new map<const char*, Shader*>();

void sendData(Game &game){

}


int main(){


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window;
    window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "Basic Game", NULL, NULL);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize glew" << endl;
        glfwTerminate();
        return -1;
    }



    Game game = *new Game(SC_WIDTH, SC_HEIGHT);
    auto startTime = std::chrono::high_resolution_clock::now();

    while(!glfwWindowShouldClose(window)){
        auto endTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        deltaTime *= 0.001;

        startTime = std::chrono::high_resolution_clock::now();

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        yPos = SC_HEIGHT - yPos;
        game.checkMouseInput(window, xPos, yPos, deltaTime);

        vector<bool> motion = game.checkKeyInput(window, deltaTime);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.checkCollisions(deltaTime);
        game.updateMotion(motion, deltaTime);
        game.renderAll();

        glfwSwapBuffers(window);
        glfwPollEvents();
        game.gameOver(window);
    }
    sendData(game);
    glfwTerminate();
    return 0;
}
