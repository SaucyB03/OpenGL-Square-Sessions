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
            enemies.push_back(new Enemy(randEnemyPosInit(), {scWidth / 10, scHeight / 10}, {0.0, 0.0}, enemyColor, 100, scWidth, scHeight));
        }
    }
}

glm::vec2 Game::randEnemyPosInit() {
    int i;
    int plat = rand() % platforms.size();
    int side = rand() % 2;
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

/*Game Constructor:
 * Initializes the Shader manager / Shader
 * Creates all inital objects, player, platforms, enemies
 */
Game::Game(int scWidth, int scHeight) : shaderManager(){
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    this->endGame = false;
    srand(time(NULL));

    //Create Platforms:
    int i;
    for(i = 0; i < NUM_PLAT_LEVELS; ++i){
        platforms.push_back(new Object(glm::vec2(0.0, (scHeight / NUM_PLAT_LEVELS) * i), glm::vec2(scWidth,50), glm::vec2(0.0,0.0), platformColor, false, scWidth, scHeight));
    }

    //create Player
    player = new Player({scWidth/2 , PLAT_THICKNESS}, {scWidth / 10,scHeight / 10}, {0.0,0.0}, playerColor, 100, scWidth, scHeight);

    //create inital enemy
    enemies.push_back(new Enemy(randEnemyPosInit(), {scWidth / 10,scHeight / 10}, {0.0,0.0}, enemyColor, 100,scWidth, scHeight));

}

/*Check Collisions:
 * Checks to see if there's any collisions between the objects
 * If I could change any method it would be this one, there's definitely a better way than what I did here
 */
void Game::checkCollisions(double deltaTime) {
    int i,j;

    //Checking bullet collisions (Buggy :(  ):
    vector<Bullet*>* currentShots = player->getCurrentShots();
    int size = currentShots->size();

    for (i = 0; i <= size-1; ++i) {
        if (currentShots->at(i)->getPosition().x < 0.0 || currentShots->at(i)->getPosition().x > scWidth ||
            currentShots->at(i)->getPosition().y < 0.0 || currentShots->at(i)->getPosition().y > scHeight) {
            //Delete the bullet once it leaves the screen, to save on computing power
            try {
                player->deleteShot(i);
                size = currentShots->size();
            }catch(out_of_range e){
                throw e;
                terminate();
            }
        } else {
            //Checks and deletes bullets when they collide with an enemy
            for (j = 0; j < enemies.size(); ++j) {
                if (currentShots->at(i)->getPosition().x <=
                    enemies.at(j)->getPosition().x + enemies.at(j)->getScale().x &&
                    currentShots->at(i)->getPosition().x >= enemies.at(j)->getPosition().x &&
                    currentShots->at(i)->getPosition().y <=
                    enemies.at(j)->getPosition().y + enemies.at(j)->getScale().y &&
                    currentShots->at(i)->getPosition().y >= enemies.at(j)->getPosition().y) {

                    //determine if the enemy is dead, and remove them from the screen if they are
                    bool dead = enemies.at(j)->changeHealth(currentShots->at(i)->getDamage());
                    player->addDamageDone(currentShots->at(i)->getDamage());
                    if (dead) {
                        defeatedEnemy(j);
                    }

                    //Delete shot if there's a collision
                    try {
                        player->deleteShot(i);
                        size = currentShots->size();
                    }catch(out_of_range e){
                        throw e;
                        terminate();
                    }
                }
            }
        }
    }

    //Check enemy collisions with player
    for(i = 0; i < enemies.size(); ++i){
        if(enemies.at(i)->getPosition().x + enemies.at(i)->getScale().x >= player->getPosition().x && enemies.at(i)->getPosition().x <= player->getPosition().x + player->getScale().y && enemies.at(i)->getPosition().y + enemies.at(i)->getScale().y >= player->getPosition().y && enemies.at(i)->getPosition().y <= player->getPosition().y + player->getScale().y){
            //If player is touched by enemy you loose 50 hp per sec
            player->changeHealth(-50 * deltaTime);

            //checks to see if player is alive
            if(player->getHealth() <= 0){
                //if players dead: end Game
                endGame = true;
            }
        }
    }

    //Platform collisions, determines if objects are on the platforms and if they are then,
    // it passes that info to the object tellin it that its grounded and cant fall more
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

/*Update Motion
 * Calls each of the objects and tells it that it should move and how long its been since last frame to get consistent movement
 * As for player the direction is based off user input
 * As for enemy the direction is based off the player's location, so it can move towards it
 */
void Game::updateMotion(vector<bool> motion, double deltaTime) {
    int i;

    //Calls the enemy objects and tells them to update their motion since last frame
    for(i = 0; i < enemies.size(); ++i){
        enemies.at(i)->move(player->getPosition(), player->getScale(), PLAT_THICKNESS, deltaTime);
    }

    //Calls teh player object and tells it the direction it should move based off user input
    if(motion[1]){
        //Player should move left:
        player->move(1, motion[0], deltaTime);
    }else if(motion[2]){
        //Player should move right:
        player->move(2, motion[0], deltaTime);
    }else{
        //Player sits still:
        player->move(0, motion[0], deltaTime);
    }

    //Tells all the live bullets to update their motion since last frame
    vector<Bullet*>* shots = player->getCurrentShots();
    for(i = 0; i < shots->size(); ++i){
        shots->at(i)->move(deltaTime);
    }

}

/*Render All
 * Pretty self-explainitory it renders all the objects onto the screen so you can see them,
 * Called every frame to update the object movement
 */
void Game::renderAll() {
    int i;

    //Render all the Platforms
    for(i = 0; i < platforms.size(); ++i){
        shaderManager.render(platforms.at(i));
    }

    shaderManager.render(player);

    for(i = 0; i < enemies.size(); ++i){
        shaderManager.render(enemies.at(i));
    }

    vector<Bullet*>* shots = player->getCurrentShots();
    for(i = 0; i < shots->size(); ++i){
        shaderManager.render(shots->at(i));
    }
}

/*Check Key Input
 * Checks if any keys have been pressed and returns the inputs as a bool vector
 */
vector<bool> Game::checkKeyInput(GLFWwindow *window, double deltaTime){
    vector<bool> keys= {false,false,false};

    //For exiting the game early
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    //For jumping
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        keys[0] = true;

    }

    //For moving left (1)/ right (2)
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        keys[2] = true;
    }else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        keys[1] = true;
    }

    //For dropping platforms
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        if(player->getGrounded() && player->getPosition().y > 2 * PLAT_THICKNESS){
            player->setDropPlat(PLAT_THICKNESS*2);
        }
    }
    return keys;
}

/*Check mouse input
 * Checks to see if the left mouse button is clicked and shoots
 * Shooting occurs in bursts of NUM_PER_BURST
 * and has a cooldown between burst of COOLDOWN seconds
 */
void Game::checkMouseInput(GLFWwindow *window, double xPos, double yPos, double deltaTime) {
    //adds delta time to total time, to know how much time has passed since boot
    totalTime += deltaTime;

    //determines if cooldown is needed / or over
    if(shotsInBurst == NUM_PER_BURST){
        shotCoolDown = totalTime;
        shotsInBurst++;
    }else if(shotsInBurst == NUM_PER_BURST+1 && totalTime - shotCoolDown > COOLDOWN){
        shotsInBurst = 0;
    }

    //Checks to see if button is pressed
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        if(shotsInBurst < NUM_PER_BURST) {
            player->shoot(xPos, yPos);
            shotsInBurst++;
        }
    }
}

/* Game Over
 * if the game is over a.k.a the player is dead then the window should close
 */
void Game::gameOver(GLFWwindow *window) {
    if(endGame){
        glfwSetWindowShouldClose(window, true);
    }
}

/* Game Info
 * Retrieves the player info from the game and returns it as a vector of strings
 */
vector<string> Game::gameInfo() {
    vector<string> info;
    //adding players total score:
    info.push_back(to_string(totalTime * (player->getDamageDone() - player->getDamageTaken())));

    //adding players damage done to enemies
    info.push_back(to_string(player->getDamageDone()));

    return info;
}
