//
// Created by brado on 3/8/2023.
//

#include "Game.h"


void Game::defeatedEnemy(int index) {
    enemies.erase(enemies.begin()+index);
    //If you defeat all the enemies of the wave then it spawns more for the next wave
    if(numWaves % 3 ==0){
        numSpawn++;
    }
    if(enemies.empty()){
        numWaves++;
        for(int i = 0; i < numSpawn; ++i) {
            enemies.push_back(new Enemy(randEnemyPosInit(), {scWidth / 10, scHeight / 10}, {0.0, 0.0}, playerColor, 100, scWidth, scHeight));
        }
    }
}

glm::vec2 Game::randEnemyPosInit() {
    int i;
    int plat = rand() % platforms.size();
    int side = rand() % 2 + 1;
    int sameSpot = 0;
    for(i = 0; i < enemies.size(); ++i) {
        if (enemies.at(i)->getPosition().y == platforms.at(plat)->getPosition().y + PLAT_THICKNESS && (enemies.at(i)->getPosition().x == -100 || enemies.at(i)->getPosition().y == scWidth + 100)) {
            sameSpot = 200;
        }
    }

    if(side == 0){
        return {-100 - sameSpot,platforms.at(plat)->getPosition().y + PLAT_THICKNESS};
    }
    return {scWidth + 100 + sameSpot ,platforms.at(plat)->getPosition().y + PLAT_THICKNESS};
}

//Public Methods:

Game::Game(int scWidth, int scHeight){
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    this->endGame = false;
    srand(time(NULL));

    int i;
    for(i = 0; i < NUM_PLAT_LEVELS; ++i){
        platforms.push_back(new Object(glm::vec2(0.0, (scHeight / NUM_PLAT_LEVELS) * i), glm::vec2(scWidth,50), glm::vec2(0.0,0.0), false, scWidth, scHeight));
    }

    player = new Player({scWidth/2 , PLAT_THICKNESS}, {scWidth / 10,scHeight / 10}, {0.0,0.0}, playerColor, 100, scWidth, scHeight);

    enemies.push_back(new Enemy(randEnemyPosInit(), {scWidth / 10,scHeight / 10}, {0.0,0.0}, playerColor, 100,scWidth, scHeight));

}

void Game::checkCollisions(double deltaTime) {
    totalTime += deltaTime;
    int i,j;

    vector<Bullet*>* currentShots = player->getCurrentShots();
    int size = currentShots->size();

    for(i = 0; i < size; ++i){
        if(currentShots->at(i)->getPosition().x < 0.0 || currentShots->at(i)->getPosition().x > scWidth || currentShots->at(i)->getPosition().y < 0.0 || currentShots->at(i)->getPosition().y > scHeight){
            player->deleteShot(i);
            size--;
            i--;
        }else {
            for (j = 0; j < enemies.size(); ++j) {
                if (currentShots->at(i)->getPosition().x <= enemies.at(j)->getPosition().x + enemies.at(j)->getScale().x && currentShots->at(i)->getPosition().x >= enemies.at(j)->getPosition().x &&currentShots->at(i)->getPosition().y <=enemies.at(j)->getPosition().y + enemies.at(j)->getScale().y &&currentShots->at(i)->getPosition().y >= enemies.at(j)->getPosition().y) {
                    bool dead = enemies.at(j)->changeHealth(currentShots->at(i)->getDamage());
                    if (dead) {
                        defeatedEnemy(j);
                    }
                    player->deleteShot(i);
                    size--;
                    i--;
                }
            }
        }
    }

    for(i = 0; i < enemies.size(); ++i){
        if(enemies.at(i)->getPosition().x + enemies.at(i)->getScale().x >= player->getPosition().x && enemies.at(i)->getPosition().x <= player->getPosition().x + player->getScale().y && enemies.at(i)->getPosition().y + enemies.at(i)->getScale().y >= player->getPosition().y && enemies.at(i)->getPosition().y <= player->getPosition().y + player->getScale().y){
            player->changeHealth(-50 * deltaTime);
            if(player->getHealth() <= 0){
                endGame = true;
            }
        }
    }

    for(i = 0; i < platforms.size(); ++i){
        if(player->getPosition().y > platforms.at(i)->getPosition().y && player->getPosition().y < platforms.at(i)->getPosition().y + PLAT_THICKNESS + COLL_BUFFER && player->getVelocity().y < 0 && player->getDropPlat() == 0){
            player->setGrounded(true);
        }
        for(j = 0; j < enemies.size(); ++j){
            if(enemies.at(j)->getPosition().y > platforms.at(i)->getPosition().y && enemies.at(j)->getPosition().y < platforms.at(i)->getPosition().y + PLAT_THICKNESS + COLL_BUFFER && enemies.at(j)->getVelocity().y < 0 && enemies.at(j)->getDropPlat() == 0){
                enemies.at(j)->setGrounded(true);
            }
        }

    }
}

void Game::updateMotion(vector<bool> motion, double deltaTime) {
    int i;

    for(i = 0; i < enemies.size(); ++i){
        enemies.at(i)->move(player->getPosition(), player->getScale(), PLAT_THICKNESS, deltaTime);
    }

    if(motion[1]){
        player->move(1, motion[0], deltaTime);
    }else if(motion[2]){
        player->move(2, motion[0], deltaTime);
    }else{
        player->move(0, motion[0], deltaTime);
    }
    vector<Bullet*>* shots = player->getCurrentShots();
    for(i = 0; i < shots->size(); ++i){
        shots->at(i)->move(deltaTime);
    }

}


void Game::renderAll() {
    int i;

    for(i = 0; i < platforms.size(); ++i){
        platforms.at(i)->display();
    }

    player->display();

    for(i = 0; i < enemies.size(); ++i){
        enemies.at(i)->display();
    }

    vector<Bullet*>* shots = player->getCurrentShots();
    for(i = 0; i < shots->size(); ++i){
        shots->at(i)->display();
    }
}

vector<bool> Game::checkKeyInput(GLFWwindow *window, double deltaTime){
    vector<bool> keys= {false,false,false};
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        keys[0] = true;

    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        keys[2] = true;
    }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        keys[1] = true;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        if(player->getGrounded() && player->getPosition().y > 2 * PLAT_THICKNESS){
            player->setDropPlat(PLAT_THICKNESS*2);
        }
    }
    return keys;
}

void Game::checkMouseInput(GLFWwindow *window, double xPos, double yPos) {
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)){
        player->shoot(xPos, yPos);
    }
}

void Game::gameOver(GLFWwindow *window) {
    if(endGame){
        glfwSetWindowShouldClose(window, true);
    }
}
