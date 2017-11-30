#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include "Background.hpp"
#include "Character.hpp"
#include "Enemy.hpp"

class GameState{
public:
    //Constructor & destructor
    GameState();
    ~GameState(){};
    
    //Texture building methods
    bool addBackground(Background *newBackground);
    bool addCharacter(sf::Texture *playerTexture, sf::Vector2u spreadsheetCorr, float pace);
    bool addEnemy(std::string enemyName, Enemy *newEnemy);
    
    void Run();
    
private:
    sf::Vector2f resolution;
    sf::View view;
    sf::RenderWindow window;
    std::vector<Background*> backGroundVector;
    std::map<std::string, Enemy*> enemy_map;
    Character Player;
    float deltaTime;
    sf::Clock clock;
};
