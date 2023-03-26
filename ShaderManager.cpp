//
// Created by brado on 3/26/2023.
//

#include "ShaderManager.h"

ShaderManager::ShaderManager(){
    shader = new Shader("../vertexShader.glsl", "../fragmentShader.glsl");
}

ShaderManager::~ShaderManager() {

}

template<typename T>
void ShaderManager::render(T *object) {

}

template<>
void ShaderManager::render<Object>(Object *object) {
    shader->bindShader();
    object->display(shader);
}

template<>
void ShaderManager::render<Player>(Player *player) {
    shader->bindShader();
    player->display(shader);
}

template<>
void ShaderManager::render<Enemy>(Enemy *enemy) {
    shader->bindShader();
    enemy->display(shader);
}

template<>
void ShaderManager::render<Bullet>(Bullet* bullet) {
    shader->bindShader();
    bullet->display(shader);
}

