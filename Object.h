//Parent Class of all onscreen objects

#ifndef M3OE_BKSOUCY_OBJECT_H
#define M3OE_BKSOUCY_OBJECT_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

#include "Shader.h"

const double APPARENT_GRAVITY = 981;

class Object {
protected:
    int scWidth;
    int scHeight;


    glm::vec2 position;
    glm::vec2 scale;
    glm::vec2 velocity;
    glm::vec3 color;

    float vertices[12];
    unsigned int indices[6] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

private:
    bool dynamic;
    //Add necessary buffers
    unsigned int va, vb, eb;

    /* assignBuffandArr
     * Assigned the Buffers and Vertex arrays for this object as well as store the information in a
     * Element array Buffer, which allows us to put 2 triangles together and have OpenGL know what to do
     */
    void assignBuffandArr();

public:
    /* Object Constructor
     * Holds info about: position, scale, velocity, color, if its dynamic / static, and the screen size
     */
    Object(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, bool dynamic, int scWidth, int scHeight);
    //Destructor: deletes the created buffers
    ~Object();

    /* Basic move
     * if there's a velocity on the object then it updates it from the last frame
     */
    void move(float deltaTime);
    /*Display
     * Applys any transformations the object has had and displays the object
     */
    void display(Shader* shader);

    /*getPostion
     * returns the objects position as a vec2
     */
    glm::vec2 getPosition();
    /*getVelocity
     * returns the objects velocity as a vec2
     */
    glm::vec2 getVelocity();
    /*getScale
     * returns the objects scale as a vec2
     */
    glm::vec2 getScale();

    /* setVelocity
     * sets the velocity to the inputted vec2
     */
    void setVelocity(glm::vec2 newVelocity);
};


#endif //M3OE_BKSOUCY_OBJECT_H
