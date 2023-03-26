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
    ShaderManager();
    ~ShaderManager();

    template<typename T>
    void  render(T* object);
};


#endif //M3OE_BKSOUCY_SHADERMANAGER_H
