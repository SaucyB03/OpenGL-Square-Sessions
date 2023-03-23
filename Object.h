//Parent Class of all onscreen objects

#ifndef M3OE_BKSOUCY_OBJECT_H
#define M3OE_BKSOUCY_OBJECT_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "Shader.h"

const float GRAVITY = -9.81;

class Object {
protected:
    int scWidth;
    int scHeight;

    Shader shader;

    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 velocity;

    float vertices[12];
    unsigned int indices[6] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

private:
    bool dynamic;
    //Add necessary buffers
    unsigned int va, vb, eb;
    void assignBuffandArr();

public:
    Object(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::mat4x3 vecColor, bool dynamic, int scWidth, int scHeight);
    ~Object();

    void move();
    void display();
};


#endif //M3OE_BKSOUCY_OBJECT_H
