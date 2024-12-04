
#include "../Headers/Sunflower.h"

Sunflower::Sunflower(std::string namein, int x, int y, sf::RenderWindow *window, TextureManager *textures,
                     game *gameInstance) : entity(std::move(namein), x, y, window),
                     textures(textures), gameInstance(gameInstance) {

    sprite = std::make_unique<sf::Sprite>();
    idleanimation = std::make_unique<Animation>(textures, "../../assets/Sunfloweridle.png", 12, sf::seconds(0.2f));
    sprite->setTexture(*idleanimation->getTexture());
    sprite->setScale(sf::Vector2f(2.f, 2.f));
    Team = 1; //for plant team
}

Sunflower::~Sunflower() = default;

void Sunflower::update() {
    sf::Time deltaTime = clock.restart(); // Get the elapsed time since the last frame and restart the clock
    idleanimation->update(deltaTime); // Update the walk animation with the elapsed time
    sprite->setTexture(*idleanimation->getTexture()); // Set the sprite's texture to the current texture of the walk animation
    sprite->setTextureRect(idleanimation->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the walk animation
    sprite->setPosition(sf::Vector2f(getXpos(), getYpos())); // Set the position of the sprite (i know it looses precision but...)
    generateSun();  // Generate sun
}

void Sunflower::renderentity() {
    window->draw(*sprite);
}

void Sunflower::generateSun() {
    if (cooldownClock.getElapsedTime() >= sf::seconds(7)) { // generates sun every 7 seconds
        gameInstance->addMoney(25); // Add money to the game
        cooldownClock.restart();    // Restart the cooldown clock
        std::cout<< "Sunflower generated sun" << std::endl;
    }
}

void Sunflower::hpchange(int dmg) {
    health -= dmg;  // Decrease the health by the damage
    if(health <= 0){    // If the health is less than or equal to 0
        flagfordelete();    // Flag the entity for deletion
    }
}
