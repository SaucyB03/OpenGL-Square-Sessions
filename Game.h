//
// Created by brado on 3/8/2023.
//

#ifndef M3OE_BKSOUCY_GAME_H
#define M3OE_BKSOUCY_GAME_H

#include <vector>
#include "Object.h"
#include "Player.h"

using namespace std;

class Game {
private:
    int SC_WIDTH;
    int SC_HEIGHT;
    bool menu;

    vector<Object> heals;
    vector<Object> spikes;
    Player player();

public:
    Game(int SC_WIDTH, int SC_HEIGHT);

    void displayMenu();
    bool getMenuStatus();

    void beginGame();
};


#endif //M3OE_BKSOUCY_GAME_H
