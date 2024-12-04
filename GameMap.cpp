
#include "../Headers/GameMap.h"
#include <iostream>

GameMap::GameMap(int x, int y, sf::RenderWindow* window, TextureManager* textures)
        : map(5, std::vector<entity*>(9, nullptr)), window(window), textures(textures) {
    inittextures(); // Initialize the textures
}

void GameMap::renderMap() {
    window->draw(*spriteBase);  // Draw the base map
    window->draw(*spriteGrass); // Draw the grass map
}

GameMap::~GameMap() {
    textures = nullptr;
}

void GameMap::placeHero(int x, int y, entity* hero) {
    map[y][x] = hero;   // Place the hero on the map
}

entity* GameMap::getHero(int x, int y) {
    return map[y][x];   // Get the hero from the map
}

void GameMap::inittextures() {

    spriteBase = std::make_unique<sf::Sprite>(*textures->getTexture("../../assets/BaseBaseMap.png"));   // Load the base map texture
    spriteGrass = std::make_unique<sf::Sprite>(*textures->getTexture("../../assets/GrassMap.png"));     // Load the grass map texture

    spriteGrass->setPosition(sf::Vector2f(150.f, 34.f)); // Set the position of the sprite

    spriteGrass->setScale(sf::Vector2f(2.f, 2.f)); // Set the scale of the sprite
    spriteBase->setScale(sf::Vector2f(2.f, 2.f)); // Set the scale of the sprite
}

int GameMap::gettileindexY(int y) { // Get the index of the tile in the y axis
    if(y>=39 && y<=107){
        return 0;
    }
    else if(y>=111 && y<=177){
        return 1;
    }
    else if(y>=183 && y<=245){
        return 2;
    }
    else if(y>=254 && y<=295){
        return 3;
    }
    else if(y>=301 && y<=361){
        return 4;
    }

    return -1;
}

int GameMap::gettileindexX(int x) { // Get the index of the tile in the x axis

    if(x>=165 && x<=209){
        return 0;
    }
    else if(x>=217 && x<=259){
        return 1;
    }
    else if(x>=265 && x<=315){
        return 2;
    }
    else if(x>=321 && x<=361){
        return 3;
    }
    else if(x>=368 && x<=419){
        return 4;
    }
    else if(x>=425 && x<=469){
        return 5;
    }
    else if(x>=475 && x<=520){
        return 6;
    }
    else if(x>=526 && x<=566){
        return 7;
    }
    else if(x>=571 && x<=620){
        return 8;
    }

    return -1;
}

int GameMap::getPeaShooterYcord(int yindex) {   // Get the y coordinate of the pea shooter
    switch (yindex) {
        case 0:
            return 40;
        case 1:
            return 110;
        case 2:
            return 175;
        case 3:
            return 240;
        case 4:
            return 300;
        default:
            return -1;
    }
}

int GameMap::getPeaShooterXcord(int xindex) {   // Get the x coordinate of the pea shooter
    switch (xindex) {
        case 0:
            return 150;
        case 1:
            return 205;
        case 2:
            return 260;
        case 3:
            return 310;
        case 4:
            return 365;
        case 5:
            return 415;
        case 6:
            return 465;
        case 7:
            return 515;
        case 8:
            return 570;
        default:
            return -1;
    }
}

int GameMap::getFriendlytileindexY(int y) {  // Get the index of the tile in the y axis
    switch (y) {
        case 40:
            return 0;
        case 110:
            return 1;
        case 175:
            return 2;
        case 240:
            return 3;
        case 300:
            return 4;
        default:
            return -1;
    }
}

int GameMap::getFriendlytileindexX(int x) { // Get the index of the tile in the x axis
    switch (x) {
        case 150:
            return 0;
        case 205:
            return 1;
        case 260:
            return 2;
        case 310:
            return 3;
        case 365:
            return 4;
        case 415:
            return 5;
        case 465:
            return 6;
        case 515:
            return 7;
        case 570:
            return 8;
        default:
            return -1;
    }
}

int GameMap::getEnemytileindexY(int y) {    // Get the index of the tile in the y axis
    switch (y) {
        case 0:
            return 0;
        case 1:
            return 70;
        case 2:
            return 140;
        case 3:
            return 190;
        case 4:
            return 260;
        default:
            return -1;
    }
}
