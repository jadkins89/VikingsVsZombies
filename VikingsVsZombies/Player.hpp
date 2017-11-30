#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Entity.hpp"

class Player: public Entity
{
public:
    Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime);
    ~Player(){};
    
    void Update(float deltaTime);
    void Draw(sf::RenderWindow &window);
    
    //Setters & Getters
    sf::Vector2f getPosition();
    
private:
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    bool attack;
    float rectHeight = 500.0f;
    float rectWidth = 500.0f;
    float startPositionX = 200.0f;
    float startPositionY = 1200.0f;
};
