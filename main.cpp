
#include <iostream>
#include "../Headers/game.h"
#include <SFML/Graphics.hpp>
#include <fstream>

#include <vector>

int main() {


    game gamed;

    while(gamed.running() && !gamed.isGameOver()){
        gamed.update();
        gamed.render();
    }

    std::cout << "Game Over" << std::endl;


    return 0;
}
