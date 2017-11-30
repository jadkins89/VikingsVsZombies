#pragma once
#include "DEFINITIONS.hpp"
#include "ResourcePath.hpp"
#include <SFML/Graphics.hpp>

class Background{
public:
    // Constructors & Destructors
    Background(){};
    Background(std::string fileName, sf::IntRect textRect, sf::Vector2f Position);
    ~Background(){};
    
    sf::Sprite getSprite();
    void Draw(sf::RenderWindow &window);
    
private:
    sf::Texture texture;
    sf::Sprite sprite;
};
