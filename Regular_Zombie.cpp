
#include "../Headers/Regular_Zombie.h"

Regular_Zombie::Regular_Zombie(std::string namein, int x, int y, sf::RenderWindow* window, TextureManager* textures, game* gameInstance)
        : entity(std::move(namein), x, y, window), textures(textures), gameInstance(gameInstance) { // Modify this line
    sprite = std::make_unique<sf::Sprite>();
    Walkanimation = std::make_unique<Animation>(textures, "../../assets/walkingzombie.png", 7, sf::seconds(0.2f));
    sprite->setTexture(*Walkanimation->getTexture());
    sprite->setScale(sf::Vector2f(2.f, 2.f));
    Attackanimation = std::make_unique<Animation>(textures, "../../assets/attackingzombie.png", 7, sf::seconds(0.2f));
    target = nullptr;
    Team = 0;
}

Regular_Zombie::~Regular_Zombie() {
    textures = nullptr;
}

void Regular_Zombie::update() {
    int frame = Walkanimation->getCurrentFrameIndex(); // Get the current frame of the walk animation
    int frameattack = Attackanimation->getCurrentFrameIndex(); // Get the current frame of the attack animation
    sf::Time deltaTime = clock.restart(); // Get the elapsed time since the last frame and restart the clock

    if (shouldAttack()) {   // If the zombie is in front of the pea shooter
        attackFlag = true;
    } else {
        attackFlag = false;
    }

    if (attackFlag && Walkanimation->getCurrentFrameIndex() == 0){  // If the zombie is in front of the pea shooter and the attack flag is true and idle animation is at the first frame
        // If the zombie is supposed to attack, update and display the attack animation
        sprite->setTexture(*Attackanimation->getTexture()); // Set the sprite's texture to the current texture of the attack animation
        sprite->setTextureRect(Attackanimation->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the attack animation
        Attackanimation->update(deltaTime); // Update the attack animation with the elapsed time

        // If the attack animation is at its last frame, execute the attack
        if (Attackanimation->getCurrentFrameIndex() == 6 && frameattack != Attackanimation->getCurrentFrameIndex()) {   // If the attack animation is at the last frame
            attack();   // Attack the pea shooter
        }
    } else {
        // If the zombie is not supposed to attack, update and display the walk animation
        Walkanimation->update(deltaTime); // Update the walk animation with the elapsed time
        sprite->setTexture(*Walkanimation->getTexture()); // Set the sprite's texture to the current texture of the walk animation
        sprite->setTextureRect(Walkanimation->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the walk animation
    }

    sprite->setPosition(sf::Vector2f(getXpos(), getYpos())); // Set the position of the sprite

    if (Walkanimation->getCurrentFrameIndex() != frame && (!attackFlag)){   // If the walk animation is at a different frame than the previous frame
        move();
    }

    sf::FloatRect spriteBounds = sprite->getGlobalBounds(); // Get the global bounds of the sprite
    hitbox = sf::Rect<float>(getXpos(), getYpos(), spriteBounds.width, spriteBounds.height);    // Set the hitbox of the zombie
}

void Regular_Zombie::renderentity() {
    window->draw(*sprite);  // Draw the sprite
}

void Regular_Zombie::move() {
    xpos -= speed;  // Move the zombie
    if(xpos < 5){   // If the zombie is out of the screen
        gameInstance->setGameOver();    // Set the game over flag
    }
}

sf::Rect<float> Regular_Zombie::getHitbox() const {
    return hitbox;
}

void Regular_Zombie::hpchange(int dmg) {
    health -= dmg;  // Decrease the health by the damage
    if (health <= 0){
        flagfordelete();    // If the health is less than or equal to 0, set the flag for deletion
    }
}

bool Regular_Zombie::shouldAttack() {
    for (auto& entity : gameInstance->getEntities()) {  // loops through all entities
        if (entity->getTeam() == 1 || entity->getTeam() == 2){  // If the entity is a peashooter or a mower
            int peaShooterY = entity->getYpos();    // Get the y position of the peashooter
            int peaShooterX = entity->getXpos();    // Get the x position of the peashooter
            int zombieY = this->getYpos();  // Get the y position of the zombie
            int zombieX = this->getXpos();  // Get the x position of the zombie
            int spriteHeight = this->sprite->getGlobalBounds().height;  // Get the height of the sprite

            // Changes so it goes down in y cord check so it doesnt flag wrong plants in a different row
            zombieY += (spriteHeight / 3)+4;

            // Check if the peashooter is next to the zombie
            if ((std::abs(peaShooterX - zombieX) <= meleeRange && std::abs(peaShooterY - zombieY) <= spriteHeight / 2)) {
                target = entity;    // Set the target to the plant
                return true;
            }
        }
    }
    target = nullptr;   // If the zombie is not in front of a peashooter, set the target to null
    return false;
}

void Regular_Zombie::attack() {
    if (target!= nullptr){  // If the target is not null
        target->hpchange(damage); // attackDamage is the damage dealt by the zombie
    }
}