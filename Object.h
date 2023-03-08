//Parent Class of all onscreen objects

#ifndef M3OE_BKSOUCY_OBJECT_H
#define M3OE_BKSOUCY_OBJECT_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

enum Shape{
    CIRCLE,
    SQUARE,
    TRIANGLE
};

class Object {
    Object(glm::vec2 position, glm::vec2 scale, Shape shape);
    ~Object();


};


#endif //M3OE_BKSOUCY_OBJECT_H
