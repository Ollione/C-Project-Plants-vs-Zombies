
#include <utility>

#include "../Headers/entity.h"


entity::entity(std::string namein, int x, int y, sf::RenderWindow* window): name(std::move(namein)), xpos(x), ypos(y), window(window) {}

int entity::getYpos() const {
    return ypos;
}

int entity::getXpos() const {
    return xpos;
}

void entity::flagfordelete() {
    deleteFlag = true;
}

bool entity::getflagfordelete() const {
    return deleteFlag;
}

sf::Rect<float> entity::getHitbox() const {
    return {};   //return empty hitbox so intersect will flag false
}

std::string entity::getName() const {
    return name;
}

int entity::getTeam() const {
    return Team;
}
