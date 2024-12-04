
#include "../Headers/Bucket_Zombie.h"

Bucket_Zombie::Bucket_Zombie(std::string namein, int x, int y, sf::RenderWindow *window, TextureManager *textures,
                             game *gameInstance) : Regular_Zombie(namein, x, y, window, textures, gameInstance) {
    health = 300;
    damage = 50;
    Walkanimation = std::make_unique<Animation>(textures, "../../assets/bucketzombiewalk.png", 7, sf::seconds(0.2f));   //OBS this uses rehular zombie as logic. only thing changed here is the animation.
    Attackanimation = std::make_unique<Animation>(textures, "../../assets/bucketzombieattack.png", 7, sf::seconds(0.2f));
    sprite->setTexture(*Walkanimation->getTexture());
}

void Bucket_Zombie::update() {
    Regular_Zombie::update();   //OBS this uses rehular zombie as logic.
}
void Bucket_Zombie::renderentity() {
    Regular_Zombie::renderentity();  //OBS this uses rehular zombie as logic.
}

void Bucket_Zombie::hpchange(int dmg) {
    Regular_Zombie::hpchange(dmg);  //OBS this uses rehular zombie as logic.
}

Bucket_Zombie::~Bucket_Zombie() = default;
