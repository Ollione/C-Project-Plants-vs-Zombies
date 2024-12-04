
#include "../Headers/Wall.h"

Wall::Wall(std::string namein, int x, int y, sf::RenderWindow *window, TextureManager *textures) : entity(std::move(namein), x, y, window) {
    sprite = std::make_unique<sf::Sprite>();
    idleanimation = std::make_unique<Animation>(textures,"../../assets/Wallidle.png" , 5, sf::seconds(0.2f));
    idleanimationDmged1 = std::make_unique<Animation>(textures,"../../assets/WallidleDmg1.png" , 5, sf::seconds(0.2f));
    idleanimationDmged2 = std::make_unique<Animation>(textures,"../../assets/WallidleDmg2.png" , 5, sf::seconds(0.2f));
    sprite->setTexture(*idleanimation->getTexture());
    sprite->setScale(sf::Vector2f(2.f, 2.f));
    Team = 1; //for plant team
}

Wall::~Wall() = default;

void Wall::update() {
    sf::Time deltaTime = clock.restart(); // Get the elapsed time since the last frame and restart the clock
    if(health >=200){
        idleanimation->update(deltaTime); // Update the idle animation with the elapsed time
        sprite->setTexture(*idleanimation->getTexture()); // Set the sprite's texture to the current texture of the idle animation
        sprite->setTextureRect(idleanimation->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the idle animation
    }
    else if (health >= 100){
        idleanimationDmged1->update(deltaTime); // Update the idle animation with the elapsed time
        sprite->setTexture(*idleanimationDmged1->getTexture()); // Set the sprite's texture to the current texture of the idle animation
        sprite->setTextureRect(idleanimationDmged1->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the idle animation
    }
    else{
        idleanimationDmged2->update(deltaTime); // Update the idle animation with the elapsed time
        sprite->setTexture(*idleanimationDmged2->getTexture()); // Set the sprite's texture to the current texture of the idle animation
        sprite->setTextureRect(idleanimationDmged2->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the idle animation
    }



    sprite->setPosition(sf::Vector2f(getXpos(), getYpos())); // Set the position of the sprite
}

void Wall::renderentity() {
    window->draw(*sprite);  // Draw the sprite
}

void Wall::hpchange(int dmg) {
    health -= dmg;  // Decrease the health by the damage
    if(health <= 0){    // If the health is less than or equal to 0
        flagfordelete();    // Flag the entity for deletion
    }
}
