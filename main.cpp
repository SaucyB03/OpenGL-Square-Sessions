//spinesquare

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "Game.h"

using namespace std;


const int SC_WIDTH = 1600;
const int SC_HEIGHT = 1600;

//map<const char*, Shader> ShaderResources::allShaders = *new map<const char*, Shader*>();

void checkInput(GLFWwindow *window) {

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(){


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "Basic Game", NULL, NULL);

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


        vector<bool> motion = game.checkInput(window, deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        game.updateMotion(motion, deltaTime);
        game.renderAll();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
