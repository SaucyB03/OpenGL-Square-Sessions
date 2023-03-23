//spinesquare

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>

#include "Game.h"

using namespace std;


const int SC_WIDTH = 1500;
const int SC_HEIGHT = 1500;

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

        game.checkInput(window, deltaTime);
        //checkInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
//        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//        shader.setUniformMat4("transform", transform);

        //game.updateMotion(deltaTime);
        game.renderAll();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
