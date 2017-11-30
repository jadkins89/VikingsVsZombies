#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "DEFINITIONS.hpp"
#include "Character.hpp"
#include "Enemy.hpp"
#include "Background.hpp"
#include "GameState.hpp"

int main()
{
    //Declares game object
    GameState Game;
    
    //Declare & Initialize background starting positions
    sf::Vector2f standardBackground(0.0f, 254.0f);
    sf::Vector2f highBackground(0.0f, 0.0f);
    sf::IntRect standardRect(0, 0, MAX_LENGTH, 1546);

    //Declare and initialize background objects
    Background Ground_Floor(GROUND_FLOOR_FILE, standardRect, standardBackground);
    Background Front_Trees(FRONT_TREES_FILE, standardRect, standardBackground);
    Background Back_Trees(BACK_TREES_FILE, standardRect, standardBackground);
    Background Grass(GRASS_FILE, standardRect, standardBackground);
    Background Back_Grass(BACK_GRASS_FILE, standardRect, highBackground);
    Background Lower_Back_Grass(LOWER_BACK_GRASS_FILE, standardRect, highBackground);
    Background Sky(BACKGROUND_FILE, standardRect, highBackground);
    Background Back_Clouds(BACK_CLOUDS_FILE, standardRect, highBackground);
    Background High_Clouds_1(HIGH_CLOUDS_FILE1, standardRect, highBackground);
    Background Clouds(CLOUDS_FILE, standardRect, standardBackground);
    
    //Add all background files in correct order
    Game.addBackground(&Sky);
    Game.addBackground(&Back_Clouds);
    Game.addBackground(&Clouds);
    Game.addBackground(&High_Clouds_1);
    Game.addBackground(&Back_Grass);
    Game.addBackground(&Lower_Back_Grass);
    Game.addBackground(&Grass);
    Game.addBackground(&Back_Trees);
    Game.addBackground(&Front_Trees);
    Game.addBackground(&Ground_Floor);
    
    // Character sprite spreadsheet declaration
    sf::Texture playerTexture;
    playerTexture.loadFromFile(resourcePath() + VIKING_FILE);
    
    //Adds main player character
    Game.addCharacter(&playerTexture, sf::Vector2u(10, 4), 0.05f);
    
    // Enemy sprite spreadsheet declaration
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile(resourcePath() + BOY_ZOMBIE);
    
    //Declare and initialize enemy objects
    Enemy zombie1(&enemyTexture, sf::Vector2u(ZB_COLUMNS, ZB_ROWS), ZOMBIE_IDLE_SPEED);
    zombie1.setScale(0.75f, 0.75f);
    Enemy zombie2(&enemyTexture, sf::Vector2u(ZB_COLUMNS, ZB_ROWS), ZOMBIE_IDLE_SPEED, true, PLAYER_POSX - 500.0f, ENEMY_POSY);
    zombie2.setScale(0.75f, 0.75f);
    Enemy zombie3(&enemyTexture, sf::Vector2u(ZB_COLUMNS, ZB_ROWS), ZOMBIE_IDLE_SPEED, false, ENEMY_POSX + 1000.0f, ENEMY_POSY);
    zombie3.setScale(0.75f, 0.75f);
    Enemy zombie4(&enemyTexture, sf::Vector2u(ZB_COLUMNS, ZB_ROWS), ZOMBIE_IDLE_SPEED, false, ENEMY_POSX + 1500.0f, ENEMY_POSY);
    zombie4.setScale(0.75f, 0.75f);
    
    //Adds Zombies to game
    Game.addEnemy("zombie1", &zombie1);
    Game.addEnemy("zombie2", &zombie2);
    Game.addEnemy("zombie3", &zombie3);
    Game.addEnemy("zombie4", &zombie4);
    
    //Run's the game window
    Game.Run();
    
    return EXIT_SUCCESS;
}
