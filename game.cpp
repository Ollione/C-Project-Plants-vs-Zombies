

#include "../Headers/game.h"
#include "../Headers/Regular_Zombie.h"
#include "../Headers/Bucket_Zombie.h"

game::game(): window(initWindow()){
    PreloadTextures();
    initVariables();
    initText();
}

game::~game() {
    for(auto &i : entities){    //delete all entities
        delete i;
    }
    for(auto &i : projectiles){ //delete all projectiles
        delete i;
    }
}

void game::update() {
    pollEvents();
    spawnZombies();
    projectileUpdate(); // Update all parts of code
    entetiesUpdate();
    hitdetect();
    if (isGameOver()) { // If the game is over, display the game over screen
        gameOvertime();
    }
}

void game:: render() {
    window->clear();
    map->renderMap();
    renderEntities();
    renderProjectiles();    // Render all parts of code
    renederUI();
    renderText();
    window->display();
}

void game::initVariables() {
    srand(time(0)); // Seed the random number generator
    map = std::make_unique<GameMap>(800, 600, window.get(), textures.get());    //create map
    ui = std::make_unique<sf::Sprite>();    //create ui
    ui->setTexture(*textures->getTexture("../../assets/ui.png"));   //set ui texture
    ui->setScale(sf::Vector2f(2.f, 2.f));   //scale ui
    ui->setPosition(sf::Vector2f(0, 384));  //set ui position
    LoadMowers();   //load mowers
}

sf::RenderWindow* game::initWindow() {
    return new sf::RenderWindow(sf::VideoMode(894, 500),"Plant vs Zombies clone", sf::Style::Titlebar | sf::Style::Close);  //create window
}

bool game::running() const {
    return window->isOpen();    //check if window is open
}

void game::pollEvents() {
    while(window->pollEvent(event)){
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::Escape){
                    window->close();
                }
                else if (event.key.code == sf::Keyboard::A) {   //place hero
                    placeHero("PeaShooter");
                }
                else if(event.key.code == sf::Keyboard::S){ //place hero
                    placeHero("Sunflower");
                }
                else if(event.key.code == sf::Keyboard::D){ //place hero
                    placeHero("Wall");
                }
                else if(event.key.code == sf::Keyboard::Space){ //sell hero
                      sellHeroAtMousePosition();
                }
                break;

        }

    }
}

void game::PreloadTextures() {
    textures = std::make_unique<TextureManager>();  //create texture manager
    std::vector<std::string> texturePaths = {   //all textures in vector to make reading easier
            "../../assets/walkingzombie.png",
            "../../assets/BaseBaseMap.png",
            "../../assets/GrassMap.png",
            "../../assets/attackingzombie.png",
            "../../assets/peashooteridle.png",
            "../../assets/peashooterattack.png",
            "../../assets/Sunfloweridle.png",
            "../../assets/bucketzombiewalk.png",
            "../../assets/bucketzombieattack.png",
            "../../assets/Wallidle.png",
            "../../assets/WallidleDmg1.png",
            "../../assets/WallidleDmg2.png",
            "../../assets/peashot.png",
            "../../assets/mower.png"
    };
    // Add more textures as needed

    for(auto &i : texturePaths){    //load all textures
        textures->getTexture(i);
    }
}

void game::addEnemy(int num) {
    int randomX = rand() % 201 + 600; // Generate 600-800 rand
    int randomY = rand() % 5; // Generate 0-4 rand which is used for what lane the zombie will spawn in
    entity* pushobj;    //create entity pointer
    if (num==1){
        pushobj = new Regular_Zombie("Regular_Zombie", randomX, map->getEnemytileindexY(randomY), window.get(), textures.get(), this);  //create zombie
    }
    else if (num==2){
        pushobj = new Bucket_Zombie("Bucket_Zombie", randomX, map->getEnemytileindexY(randomY), window.get(), textures.get(), this);    //create bucket zombie
    }

    entities.push_back(pushobj);    //push zombie to entities vector
    std::sort(entities.begin(), entities.end(), [](entity* a, entity* b) { return a->getYpos() < b->getYpos(); });  //sort entities vector
}

void game::placeHero(std::string heroName) {

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);   //get mouse position
    int Xindex = map->gettileindexX(mousePosition.x);   //get tile index
    int Yindex = map->gettileindexY(mousePosition.y);   //get tile index

    if(Xindex == -1 || Yindex == -1){   //check if index is valid
        return;
    }
    if ((map->getHero(Xindex, Yindex) != nullptr)){   //check if tile is empty
        return;
    }
    if(!buyhero(heroName)){ //check if player has enough money
        return;
    }


    if(heroName == "PeaShooter"){   //create heros depending on string
        addPeaShooter(map->getPeaShooterXcord(Xindex), map->getPeaShooterYcord(Yindex), Xindex, Yindex);
    }
    else if(heroName == "Sunflower"){
        addSunflower(map->getPeaShooterXcord(Xindex), map->getPeaShooterYcord(Yindex), Xindex, Yindex);
    }
    else if(heroName == "Wall"){
        addWall(map->getPeaShooterXcord(Xindex), map->getPeaShooterYcord(Yindex), Xindex, Yindex);
    }
}

void game::addprojectile(int x, int y, int speed, int damage) {
    auto* pushobj = new PeaShot("peashot", x, y, window.get(), textures.get(), damage, speed, sf::seconds(0.01f));   //create projectile
    projectiles.push_back(pushobj); //push projectile to vector
}

void game::hitdetect() {
    for (auto& peaShot : projectiles) { //loops all projectiles
        for (auto& entity : entities) { //loops all entities
            if (peaShot->getHitbox().intersects(entity->getHitbox())) { //check if projectile hits entity
                std::cout << "Hit detected!" << std::endl;
                entity->hpchange(peaShot->getdmg());    //call hpchange function
                peaShot->flagfordelete();   //flag projectile for deletion
            }
        }
    }
}

void game::addPeaShooter(int x, int y, int xindex, int yindex) {
    auto* pushobj = new PeaShooter("PeaShooter", x, y, window.get(), textures.get(), this);   //create pea shooter
    entities.push_back(pushobj);    //push pea shooter to entities vector
    std::sort(entities.begin(), entities.end(), [](entity* a, entity* b) { return a->getYpos() < b->getYpos(); });  //sort entities vector
    map->placeHero(xindex, yindex, pushobj);    //place pea shooter on map
}

bool game::buyhero(const std::string& heroName) {
    if(heroName == "PeaShooter" && Money >= 100){   //check if player has enough money
        Money -= 100;
        return true;
    }
    else if(heroName == "Sunflower" && Money >= 50){
        Money -= 50;
        return true;
    }
    else if(heroName == "Wall" && Money >= 50){
        Money -= 50;
        return true;
    }

    return false;   //return false if player doesnt have enough money
}

void game::sellhero(entity* sellEntity) {
    if(sellEntity->getName() == "PeaShooter"){  //sell hero depending on name
        Money += 50;
    }
    else if(sellEntity->getName() == "Sunflower"){
        Money += 25;
    }
    else if(sellEntity->getName() == "Wall"){
        Money += 25;
    }

    // Remove the hero from the entities vector
    entities.erase(std::remove(entities.begin(), entities.end(), sellEntity), entities.end());

    // Delete the hero
    delete sellEntity;
}

std::vector<entity *> &game::getEntities() {
    return entities;    //return entities vector pointer
}

void game::addMoney(int amount) {
    if(Money<1000)  //add money
        Money += amount;
}

void game::addSunflower(int x, int y, int xindex, int yindex) {
    auto* pushobj = new Sunflower("Sunflower", x, y, window.get(), textures.get(), this);   //create sunflower
    entities.push_back(pushobj);    //push sunflower to entities vector
    std::sort(entities.begin(), entities.end(), [](entity* a, entity* b) { return a->getYpos() < b->getYpos(); });  //sort entities vector
    map->placeHero(xindex, yindex, pushobj);    //place sunflower on map
}

void game::addWall(int x, int y, int xindex, int yindex) {
    auto* pushobj = new Wall("Wall", x, y, window.get(), textures.get());   //create wall
    entities.push_back(pushobj);    //push wall to entities vector
    std::sort(entities.begin(), entities.end(), [](entity* a, entity* b) { return a->getYpos() < b->getYpos(); });  //sort entities vector
    map->placeHero(xindex, yindex, pushobj);    //place wall on map
}

void game::setGameOver() {
    gameover = true;
}

bool game::isGameOver() {
    return gameover;
}

void game::LoadMowers() {
    int array[5] = {39, 109, 174, 239, 299};    //array of y positions
    for (int i = 0; i < 5; i++) {   //create mowers
        auto* pushobj = new Mower("Mower", 110, array[i], window.get(), textures.get(), this);
        entities.push_back(pushobj);
    }

    std::sort(entities.begin(), entities.end(), [](entity* a, entity* b) { return a->getYpos() < b->getYpos(); });  //sort entities vector
}

void game::spawnZombies() {

    sf::Time spawnElapsed = zombieSpawnClock.getElapsedTime();  //get elapsed time
    if (spawnElapsed.asSeconds() >= 10.0f) { // Spawn zombies every 10 seconds
        for (int i = 0; i < zombiesToSpawn; i++) {  //spawn zombies
            addEnemy(1);
        }
        for(int i = 0; i < bucketZombieSpawn; i++){   //spawn bucket zombies
            addEnemy(2);
        }

        zombieSpawnClock.restart(); // Restart the clock
    }

    sf::Time increaseElapsed = zombieIncreaseClock.getElapsedTime();    //get elapsed time
    sf::Time bucketElapsed = bucketZombieSpawnClock.getElapsedTime();   //get elapsed time
    if (increaseElapsed.asSeconds() >= 20.0f) { // Increase zombiesToSpawn every 20 seconds
        zombiesToSpawn++;
        zombieIncreaseClock.restart();
    }
    if(bucketElapsed.asSeconds() >= 60.0f){
        bucketZombieSpawn++;
        bucketZombieSpawnClock.restart();
    }
}

void game::projectileUpdate() {
    for (auto it = projectiles.begin(); it != projectiles.end();) {   //update all projectiles and deletes them if they are flagged for deletion
        (*it)->update();
        if ((*it)->getflagfordelete()) {
            delete *it; // Call the destructor
            it = projectiles.erase(it); // Remove the projectile from the container
        } else {
            ++it;
        }
    }
}

void game::entetiesUpdate() {
    for (auto it = entities.begin(); it != entities.end();) {   //update all entities and deletes them if they are flagged for deletion
        (*it)->update();
        if ((*it)->getflagfordelete()) {
            if((*it)->getTeam() == 1){
                map->placeHero(map->getFriendlytileindexX((*it)->getXpos()), map->getFriendlytileindexY((*it)->getYpos()), nullptr);    // DOESNT DELETE CORRECTLY
            }
            delete *it; // Call the destructor
            it = entities.erase(it); // Remove the entity from the container
        } else {
            ++it;
        }
    }
}

void game::renderEntities() {
    for(auto &i : entities){    //render all entities
        i->renderentity();
    }
}

void game::renderProjectiles() {
    for(auto &i : projectiles){ //render all projectiles
        i->renderentity();
    }
}

void game::initText() {
    if (!font.loadFromFile("../../assets/Avilock Bold.ttf"))    //load font
    {
        std::cout << "Error loading font" << std::endl;
        return;
    }
    moneyText.setFont(font);
    moneyText.setCharacterSize(24);
    moneyText.setFillColor(sf::Color::Blue);    //set text properties
    moneyText.setPosition(815, 410);

    timerText.setFont(font);
    timerText.setCharacterSize(14);
    timerText.setFillColor(sf::Color::Blue);    //set text properties
    timerText.setPosition(810, 470);
}

void game::renderText() {
    moneyText.setString(std::to_string(Money));   //set text
    window->draw(moneyText);    //draw text

    std::ostringstream stream;  //make a stream
    stream << std::fixed << std::setprecision(1) << TotalTime.getElapsedTime().asSeconds();   //set stream with a precision of 1 decimal
    std::string s = stream.str();   //convert stream to string

    timerText.setString(s); //set text
    window->draw(timerText);    //draw text
}

void game::gameOvertime() {
    window->clear(sf::Color::Black);    //clear window
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("GAME OVER\nTime Survived: " + std::to_string(TotalTime.getElapsedTime().asSeconds()) + " sec");   //set text
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(350, window->getSize().y / 2); // Center of the window
    window->draw(scoreText);
    window->display();
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {  //loops till window is closed
                window->close();
            }
        }
    }
}

void game::renederUI() {
    window->draw(*ui);  //draw ui
}

void game::sellHeroAtMousePosition() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
    int Xindex = map->gettileindexX(mousePosition.x);
    int Yindex = map->gettileindexY(mousePosition.y);   //get mouse position

    if(Xindex == -1 || Yindex == -1){   //check if index is valid
        return;
    }

    if(map->getHero(Xindex, Yindex) == nullptr){    //check if tile is empty
        return;
    }

    sellhero(map->getHero(Xindex, Yindex));   //sell hero
    map->placeHero(Xindex, Yindex, nullptr);    //set tile as empty
}
