
#include "../Headers/PeaShot.h"

PeaShot::PeaShot(std::string namein, int x, int y, sf::RenderWindow* window, TextureManager* textures, int damage, int speed, sf::Time speedInterval)
        : entity(std::move(namein), x, y, window), speedInterval(speedInterval),speed(speed), damage(damage), textures(textures) { // Modify this line
    sprite = std::make_unique<sf::Sprite>();
    sprite->setTexture(*textures->getTexture("../../assets/peashot.png"));
    sprite->setScale(sf::Vector2f(2.f, 2.f));
    sprite->setPosition(sf::Vector2f(getXpos(), getYpos())); // Set the initial position of the sprite
    Team = -1; //for none team
}

PeaShot::~PeaShot() {
    textures = nullptr;
}

void PeaShot::update() {

    sf::Time elapsedTime = clock.getElapsedTime();  // Get the elapsed time since the last frame
    if (elapsedTime >= speedInterval) { // If the elapsed time is greater than the speed interval
        xpos += speed;  // Move the projectile
        if(xpos > 800){ // If the projectile is out of the screen
            flagfordelete();
        }
        sprite->setPosition(sf::Vector2f(getXpos(), getYpos()));
        clock.restart();
    }
    hitbox = sf::Rect<float>(getXpos(), getYpos(), sprite->getTexture()->getSize().x, sprite->getTexture()->getSize().y);   // Set the hitbox of the projectile
}

void PeaShot::renderentity() {
    window->draw(*sprite);  // Draw the sprite
}

sf::Rect<float> PeaShot::getHitbox() const {
    return hitbox;
}

int PeaShot::getdmg() const {
    return damage;  // Get the damage of the projectile
}
