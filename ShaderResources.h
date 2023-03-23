//
// Created by brado on 3/23/2023.
//

#ifndef M3OE_BKSOUCY_SHADERRESOURCES_H
#define M3OE_BKSOUCY_SHADERRESOURCES_H

#include "Shader.h"
#include <map>

using namespace std;

class ShaderResources {
private:
    static map<string, Shader> allShaders;
public:
    static void addShader(string name);

    static Shader getShader(string name);
};


#endif //M3OE_BKSOUCY_SHADERRESOURCES_H
