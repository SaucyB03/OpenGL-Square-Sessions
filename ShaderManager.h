//
// Created by brado on 3/26/2023.
//

#ifndef M3OE_BKSOUCY_SHADERMANAGER_H
#define M3OE_BKSOUCY_SHADERMANAGER_H

#include "Shader.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"



class ShaderManager {
private:
    Shader* shader;
public:
    /*Constructor
     * Initializes the shader
     */
    ShaderManager();
    ~ShaderManager();

    /*render
     * based off the entered type either Object or one of its child classes
     * it calls their respective display functions, centralizing the render calls and allowing all objects
     * to render using one shader but without needed to create a seperate shader for each object
     */
    template<typename T>
    void  render(T* object);
};


#endif //M3OE_BKSOUCY_SHADERMANAGER_H
