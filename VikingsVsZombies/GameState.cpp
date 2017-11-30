#include "GameState.hpp"

GameState::GameState(){
    // Get the screen resolution and create an SFML window and View
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    
    //Declare and initialize view
    view.reset(sf::FloatRect(0,0, resolution.x, resolution.y));
    
    //Declare and initialize Window
    window.create(sf::VideoMode(resolution.x, resolution.y), "Game Window", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    
    //Hides Mouse
    window.setMouseCursorVisible(false);
}

bool GameState::addBackground(Background *newBackground){
    backGroundVector.push_back(newBackground);
}

bool GameState::addCharacter(sf::Texture *playerTexture, sf::Vector2u spreadsheetCorr, float pace){
    Player = Character(playerTexture, spreadsheetCorr, pace);
}

bool GameState::addEnemy(std::string enemyName, Enemy *newEnemy){
    enemy_map[enemyName] = newEnemy;
}

void GameState::Run(){
    // Start the game loop
    
    //Vector to track center of the display
    sf::Vector2f position(resolution.x / 2, resolution.y / 2);
    sf::Vector2f movement(0.0f, 0.0f);
    
    //Declaring typedef for readability
    typedef std::map<std::string, Enemy*> enemy_map_def;
    
    while (window.isOpen())
    {
        // Gives us delta time (time that passes between loops)
        deltaTime = clock.restart().asSeconds();
        
        // Process events
        sf::Event event; //Event is a union type object, only one can exist at a time
        
        //Looks for "events" to occur on/to window
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        //Keeps view centered as character moves through rendered background
        if (Player.getPosition().x + PLAYER_HALF_WIDTH >= MAX_LENGTH - (resolution.x / 2.0f)){
            position.x = view.getCenter().x;
        }
        //Updates position of center of character
        else if (Player.getPosition().x + PLAYER_HALF_WIDTH > resolution.x / 2.0f){
            position.x = Player.getPosition().x + PLAYER_HALF_WIDTH;
        }
        else
            position.x = resolution.x / 2;
        
        //Repositions screen to stay center
        view.setCenter(position);
        window.setView(view);
        
        //Render background objects
        for(int i = 0; i < backGroundVector.size(); i++){
            backGroundVector[i]->Draw(window);
        }
        
        sf::RectangleShape door(sf::Vector2f(87*2, 87*2));
        sf::Texture doorTexture;
        doorTexture.loadFromFile(resourcePath() + ARROW_FILE);
        doorTexture.setSmooth(true);
        door.setTexture(&doorTexture);
        door.setPosition(MAX_LENGTH - 400, resolution.y - 400);
        window.draw(door);
        
        Player.Draw(window);
        
        //Loops through enemies; erasing them if they are dead, performs actions otherwise
        
        bool collision = false;
        for(enemy_map_def::iterator it = enemy_map.begin(); it != enemy_map.end(); it++){
            if (!it->second->getDead()){
                if (!it->second->getDying()){
                    if (Player.Collision(it->second->getSprite())){
                        collision = true;
                    }
                }
                it->second->Collision(Player.getSprite());
                it->second->Draw(window);
            }
        }
        if (collision == false)
            Player.setCollisionIndicator("false");
        
        // Update the window
        window.display();
        Player.Update(deltaTime);
        
        //Updates all enemiesa
        for(enemy_map_def::iterator it = enemy_map.begin(); it != enemy_map.end(); it++){
        it->second->Update(deltaTime);
        }
        
        // Clear screen of previous rendered images
        window.clear();
    }
}
