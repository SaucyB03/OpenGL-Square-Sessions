//Parent Class of all onscreen objects

#ifndef M3OE_BKSOUCY_OBJECT_H
#define M3OE_BKSOUCY_OBJECT_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>


const float GRAVITY = -9.81;

class Object {
protected:
    int scWidth;
    int scHeight;

    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 velocity;
    bool dynamic;

    //Add necessary buffers
    unsigned int va;
    unsigned int vb;
    unsigned int eb;

    float vertices[12];
    unsigned int indices[6] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    void assignBuffandArr(float vertices[], unsigned int indices[]);

public:
    Object(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, bool dynamic, int scWidth, int scHeight);
    ~Object();

    void move(bool grounded, float speed, bool move, float deltaTime);
    void display();
};


#endif //M3OE_BKSOUCY_OBJECT_H
