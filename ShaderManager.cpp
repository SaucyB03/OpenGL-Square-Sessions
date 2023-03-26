//
// Created by brado on 3/26/2023.
//

#include "ShaderManager.h"

/*Constructor
 * Initializes the shader
 */
ShaderManager::ShaderManager(){
    shader = new Shader("../vertexShader.glsl", "../fragmentShader.glsl");
}

ShaderManager::~ShaderManager() {

}

/*render
 * based off the entered type either Object or one of its child classes
 * it calls their respective display functions, centralizing the render calls and allowing all objects
 * to render using one shader but without needed to create a seperate shader for each object
 */
template<typename T>
void ShaderManager::render(T *object) {

}

//Of type Object
template<>
void ShaderManager::render<Object>(Object *object) {
    shader->bindShader();
    object->display(shader);
}
//Of type Player
template<>
void ShaderManager::render<Player>(Player *player) {
    shader->bindShader();
    player->display(shader);
}

//Of type Enemy
template<>
void ShaderManager::render<Enemy>(Enemy *enemy) {
    shader->bindShader();
    enemy->display(shader);
}

//Of Type Bullet
template<>
void ShaderManager::render<Bullet>(Bullet* bullet) {
    shader->bindShader();
    bullet->display(shader);
}

