
#include "../Headers/Mower.h"

Mower::Mower(std::string namein, int x, int y, sf::RenderWindow* window, TextureManager* textures, game* gameInstance)
        : entity(std::move(namein), x, y, window), textures(textures), gameInstance(gameInstance) { // Modify this line
    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(*textures->getTexture("../../assets/mower.png"));
    sprite->setScale(sf::Vector2f(2.f, 2.f));
    sprite->setPosition(sf::Vector2f(getXpos(), getYpos()));
    Team = 2;
}

Mower::~Mower() = default;

void Mower::update() {
    if (wipeMode) {
        checkForZombiesCollison();
        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 0.01f) {
            xpos += 2;  // Move the mower
            sprite->setPosition(sf::Vector2f(getXpos(), getYpos()));    // Set the position of the sprite
            if (xpos > 800) {   // If the mower is out of the screen
                flagfordelete();
            }
            clock.restart();    // Restart the clock
        }
        hitbox = sf::Rect<float>(getXpos(), getYpos()+10, sprite->getTexture()->getSize().x, sprite->getTexture()->getSize().y-30); // Set the hitbox of the mower
    }
}

void Mower::renderentity() {
    window->draw(*sprite);  // Draw the sprite
}

void Mower::hpchange(int dmg) {
    wipeMode = true;
}

void Mower::checkForZombiesCollison() {
    for (auto &zombie : gameInstance->getEntities()) {  // Check for collision with zombies
        if (zombie->getTeam()==0 && zombie->getHitbox().intersects(getHitbox())) {  // If the mower collides with a zombie
            zombie->hpchange(1000); // Kill the zombie
        }
    }
}

sf::Rect<float> Mower::getHitbox() const {
    return hitbox;
}
