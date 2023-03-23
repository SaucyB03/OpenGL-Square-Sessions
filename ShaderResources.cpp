//
// Created by brado on 3/23/2023.
//

#include "ShaderResources.h"

void ShaderResources::addShader(string name) {
    allShaders.insert({name, *new Shader("../vertexShader.glsl", "../fragmentShader.glsl")});
}

Shader ShaderResources::getShader(string name) {
    try{
        return allShaders.at(name);
    }catch(out_of_range){
        throw "Error: getShader(): Shader name entered has not been created";
    }
}
