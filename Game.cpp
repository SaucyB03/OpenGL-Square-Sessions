//
// Created by brado on 3/8/2023.
//

#include "Game.h"

Game::Game(int SC_WIDTH, int SC_HEIGHT) {
    this-> SC_WIDTH = SC_WIDTH;
    this-> SC_HEIGHT = SC_HEIGHT;
    menu = true;
    displayMenu();
}

void Game::displayMenu() {

}

bool Game::getMenuStatus() {
    return menu;
}

void Game::beginGame() {

}
