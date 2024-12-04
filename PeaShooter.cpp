
#include "../Headers/PeaShooter.h"

PeaShooter::PeaShooter(std::string namein, int x, int y, sf::RenderWindow* window, TextureManager* textures, game* gameInstance)
        : entity(std::move(namein), x, y, window), textures(textures), gameInstance(gameInstance)  { // Modify this line
    sprite = std::make_unique<sf::Sprite>();
    idleanimation = std::make_unique<Animation>(textures, "../../assets/peashooteridle.png", 8, sf::seconds(0.2f));
    sprite->setTexture(*idleanimation->getTexture());
    sprite->setScale(sf::Vector2f(2.f, 2.f));
    Attackanimation = std::make_unique<Animation>(textures, "../../assets/peashooterattack.png", 3, sf::seconds(0.2f));
    Team = 1; //for plant team
}

PeaShooter::~PeaShooter() {
    textures = nullptr;
}

void PeaShooter::update() {
    int frame = Attackanimation->getCurrentFrameIndex();    // Get the current frame of the attack animation
    sf::Time deltaTime = clock.restart(); // Get the elapsed time since the last frame and restart the clock

    if (shouldAttack() != attackFlag) { // If the zombie is in front of the pea shooter and the attack flag is not the same as the should attack flag
        setattack();
    }

    if (attackFlag && idleanimation->getCurrentFrameIndex() == 0 && !cooldown){ // If the zombie is in front of the pea shooter and the attack flag is true
        sprite->setTexture(*Attackanimation->getTexture());
        sprite->setTextureRect(Attackanimation->getCurrentFrame());
        Attackanimation->update(deltaTime); // Update the attack animation with the elapsed time
        if(Attackanimation->getCurrentFrameIndex() == 2 && frame != Attackanimation->getCurrentFrameIndex()){   // If the attack animation is at the last frame
            shoot();    // Shoot a projectile
            cooldown = true; // Start the cooldown
            cooldownClock.restart(); // Restart the cooldown clock
        }

    } else {    //if pea shooter is not attacking do idle animation
        idleanimation->update(deltaTime); // Update the idle animation with the elapsed time
        sprite->setTexture(*idleanimation->getTexture()); // Set the sprite's texture to the current texture of the walk animation
        sprite->setTextureRect(idleanimation->getCurrentFrame()); // Set the sprite's texture rectangle to the current frame of the walk animation

        // If the cooldown is active and the cooldown period has passed, end the cooldown
        if (cooldown && cooldownClock.getElapsedTime() >= sf::seconds(1)) { // Change the cooldown period as needed
            cooldown = false;
        }
    }

    sprite->setPosition(sf::Vector2f(getXpos(), getYpos()));
}

void PeaShooter::renderentity() {
    window->draw(*sprite);  // Draw the sprite
}

void PeaShooter::shoot() {
    gameInstance->addprojectile(getXpos()+50, getYpos()+5, 1, 10);  // Add a projectile to the game
}

void PeaShooter::hpchange(int dmg) {
    health -= dmg;  // Decrease the health by the damage
    if(health <= 0){    // If the health is less than or equal to 0
        flagfordelete();
    }
}

bool PeaShooter::shouldAttack() const {

    for (auto& entity : gameInstance->getEntities()) {  // Check if the pea shooter should attack by taking positions of zombies
        if (entity->getTeam() == 0) {
            int zombieY = entity->getYpos();    // Get the zombie's y position
            int zombieX = entity->getXpos();    // Get the zombie's x position
            int peaShooterY = this->getYpos();  // Get the pea shooter's y position
            int peaShooterX = this->getXpos();  // Get the pea shooter's x position
            int spriteHeight = this->sprite->getGlobalBounds().height;  // Get the height of the sprite

            // Adjust the peaShooterY to be the top half of the sprite's height
            peaShooterY -= spriteHeight / 2;

            // Check if the zombie is in front of the peashooter and if the cooldown is not active
            if (zombieX > peaShooterX && std::abs(zombieY - peaShooterY) <= spriteHeight / 2 && !cooldown) {    // checks the abosolute value of the difference between the y positions of the zombie and the pea shooter also checks so its infronht of the plant.
                return true;
            }
        }
    }
    return false;
}

void PeaShooter::setattack() {  // Set the attack flag
    attackFlag = !attackFlag;
}

